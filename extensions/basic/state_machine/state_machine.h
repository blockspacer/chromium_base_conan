#pragma once

#include <atomic>
#include <vector>

#include <base/macros.h>
#include <base/containers/flat_map.h>
#include <base/threading/thread_collision_warner.h>
#include <base/callback.h>

#include <basic/rvalue_cast.h>
#include <basic/status/status_macros.h>

namespace basic {

/// \note Not thread-safe i.e. does not use any synchronization primitives
/// (only with minimal thread-safety checks in debug builds)
/// \note State must be a primitive type (for the std::atomic<State> typecast to work),
/// and enums require an integer binding.
// The StateMachine class is a
// general state machine framework which executes
// a client's callback functions upon entry and exit of each state.
// Specifically, entry actions are executed
// upon entry into a state, either when
// transitioning to the initial state or to a subsequent state.
// Conversely, exit actions are executed when
// transitioning out of a state.
//
// EXAMPLE
//
// class ExampleStateMachine {
//  public:
//   enum State {
//     UNINITIALIZED = 0,
//     STARTED = 1,
//     PAUSED = 2,
//     TERMINATED = 2,
//     FAILED = 3,
//   };
//
//   enum Event {
//     START = 0,
//     PAUSE = 1,
//     TERMINATE = 2,
//     FAULT = 3,
//   };
//
//   using StateMachineType =
//       StateMachine<
//         ExampleStateMachine::State
//         , ExampleStateMachine::Event
//       >;
//
//   ExampleStateMachine(
//     const State& initial_state)
//     : sm_(initial_state, FillStateTransitionTable())
//   {
//     AddStateCallbackFunctions();
//   }
//
//   // Adds an event for the StateMachine to process, with an optional reason
//   // describing why the event is added. In the case where an entry/exit action
//   // fails during a transition, the recovery_event is set based on the
//   // recommended course of action.
//   ::basic::Status ProcessEvent(
//     Event event
//     , ::base::StringPiece reason
//     , Event* recovery_event)
//   {
//     LOG(INFO) << "Processing Event " << event << " [" << reason << "]"
//               << " to the SM.";
//     return sm_->ProcessEvent(event, reason, recovery_event);
//   }
//
//   // Defines all valid transitions for the state machine.
//   // The transition table represents the following state diagram:
//   // ASCII diagram generated using http://asciiflow.com/
//   //      +-------------------+----------------+----------------+----------------+
//   //      |                   ^                ^                ^                |
//   //      |                   |     START      |                |                |
//   //      |                   |   +---------+  |                |                |
//   //      |                   |   |         |  |                |                |
//   //      |                   +   v         +  |                +                v
//   // UNINITIALIZED         STARTED         PAUSED          TERMINATED         FAILED
//   //    +   +              ^  +  +          ^  +             ^   ^  ^
//   //    |   |              |  |  |          |  |             |   |  |
//   //    |   +---------------  +  +----------+  +-------------+   |  |
//   //    |         START       |      PAUSE           TERMINATE   |  |
//   //    |                     |                                  |  |
//   //    |                     |                                  |  |
//   //    |                     |                                  |  |
//   //    |                     |                                  |  |
//   //    |                     +----------------------------------+  |
//   //    |                                   TERMINATE               |
//   //    +-----------------------------------------------------------+
//   //                              TERMINATE
//   //
//   MUST_USE_RETURN_VALUE
//   StateMachineType::TransitionTable FillStateTransitionTable()
//   {
//     StateMachineType::TransitionTable sm_table_;
//
//     //    [state][event] -> next state
//     sm_table_[UNINITIALIZED][START] = STARTED;
//     sm_table_[UNINITIALIZED][TERMINATE] = TERMINATED;
//     sm_table_[UNINITIALIZED][FAULT] = FAILED;
//
//     sm_table_[STARTED][PAUSE] = PAUSED;
//     sm_table_[STARTED][TERMINATE] = TERMINATED;
//     sm_table_[STARTED][FAULT] = FAILED;
//
//     sm_table_[PAUSED][TERMINATE] = TERMINATED;
//     sm_table_[PAUSED][FAULT] = FAILED;
//
//     sm_table_[TERMINATED][TERMINATE] = TERMINATED;
//     sm_table_[TERMINATED][FAULT] = FAILED;
//
//     sm_table_[FAILED][FAULT] = FAILED;

//     return sm_table_
//   }
//
//   // Adds the entry and exit functions for each state.
//   void AddStateCallbackFunctions()
//   {
//     // Warning: all callbacks must be used
//     // within the lifetime of the state machine.
//     sm_->AddExitAction(UNINITIALIZED,
//       [this] (Event event, State next_state, Event* recovery_event)
//       {
//         State prev_state = sm_->currentState();
//         return ::basic::OkStatus();
//       });
//     sm_->AddEntryAction(STARTED,
//       [this] (Event event, State next_state, Event* recovery_event)
//       {
//         State prev_state = sm_->currentState();
//         return ::basic::OkStatus();
//       });
//     sm_->AddEntryAction(PAUSED,
//       [this] (Event event, State next_state, Event* recovery_event)
//       {
//         State prev_state = sm_->currentState();
//         return ::basic::OkStatus();
//       });
//     sm_->AddEntryAction(FAILED,
//       [this] (Event event, State next_state, Event* recovery_event)
//       {
//         State prev_state = sm_->currentState();
//         return ::basic::Status(::util::error::INTERNAL, "Failures are fun!")
//       });
//   }
//
//   StateMachineType sm_;
// };
//
// ExampleStateMachine example_sm(STARTED);
// Event recovery_event;
// if (!example_sm.ProcessEvent(PAUSE, "", &recovery_event).ok()) {
//   // Process the recovery event.
// }

template <typename State, typename Event>
class StateMachine {
 public:
  // The CallbackType is the function type for
  // a client's entry and exit actions.
  // It requires the intended next_state and the
  // incoming event which triggered the transition.
  // An internal error is returned when necessary, and
  // a recovery_event (a followup event in response to the issue)
  // can be set based on the recommended course of action.
  // However, the recovery_event is not automatically executed;
  // it is merely a suggestion that may be used to
  // recover the state machine.
  using CallbackType
    = ::base::RepeatingCallback<
        ::basic::Status(
          Event event, State next_state, Event* recovery_event)
      >;

  // A TransitionTable stores the valid transitions,
  // indexed by the outgoing
  // state and the incoming event;
  // table_[current_state_][incoming_event] yields
  // the next state, if it exists.
  using TransitionTable =
    ::base::flat_map<State, ::base::flat_map<Event, State>>;

  // It is the client's responsibility
  // to ensure that the initial state is safe
  // to enter before calling this constructor.
  explicit StateMachine(
    const State& initial_state
    , const TransitionTable& table)
    : current_state_(initial_state)
    , table_(table)
  {
    DFAKE_SCOPED_LOCK(debug_thread_collision_warner_);
  }

  explicit StateMachine(
    const State& initial_state
    // If TransitionTable is big,
    // than you may want to |std::move| it
    , TransitionTable&& table)
    : current_state_(initial_state)
    , table_(RVALUE_CAST(table))
  {
    DFAKE_SCOPED_LOCK(debug_thread_collision_warner_);
  }

  // Entry actions are executed in the order they are added.
  void AddEntryAction(
    const State& state
    , const CallbackType& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_LOCK(debug_thread_collision_warner_);
    entry_actions_[state].push_back(callback);
  }

  // Exit actions are executed in the order they are added.
  void AddExitAction(
    const State& state
    , const CallbackType& callback) NO_EXCEPTION
  {
    DFAKE_SCOPED_LOCK(debug_thread_collision_warner_);
    exit_actions_[state].push_back(callback);
  }

  // Evaluates whether the given event triggers a state transition.
  // If so, it performs any entry and exit actions.
  // The reason parameter describes why the
  // event was added to the StateMachine.
  MUST_USE_RETURN_VALUE
  ::basic::Status ProcessEvent(
    const Event& event
    // optional reason describing why the event is added
    , ::base::StringPiece reason
    // In the case where an entry/exit action
    // fails during a transition, the recovery_event is set based on the
    // recommended course of action.
    , Event* recovery_event) NO_EXCEPTION
  {
    DFAKE_SCOPED_LOCK(debug_thread_collision_warner_);
    return ProcessEventUnlocked(event, reason, recovery_event);
  }

  MUST_USE_RETURN_VALUE
  State currentState() const NO_EXCEPTION
  {
    return current_state_.load();
  }

 private:
  // Performs the actions of ProcessEvent.
  MUST_USE_RETURN_VALUE
  ::basic::Status ProcessEventUnlocked(
    const Event& event
    , ::base::StringPiece reason
    , Event* recovery_event) NO_EXCEPTION
  {
    LOG_CALL(DVLOG(99));

    UNREFERENCED_PARAMETER(reason);

    DFAKE_SCOPED_RECURSIVE_LOCK(debug_thread_collision_warner_);

    // Do not change states if the transition is invalid.
    CONSUME_OR_RETURN(
      State next_state, NextState(current_state_.load(), event));
    // FIXME: Wait for CONSUME_OR_RETURN impl with error message
      // _.LogWarning() << "Event " << event << " [" << reason <<
      //"] was discarded in State " << current_state_);

    // Perform exit actions for the current state.
    for (const auto& exit_action : exit_actions_[current_state_.load()]) {
      RETURN_WITH_MESSAGE_IF_NOT_OK(
        exit_action.Run(event, next_state, recovery_event)) <<
        "Failed to perform exit action of state " << current_state_.load() <<
        " in transition to " << next_state << ".";
    }

    // Perform entry actions for the next state.
    for (const auto& entry_action : entry_actions_[next_state]) {
      RETURN_WITH_MESSAGE_IF_NOT_OK(
        entry_action.Run(event, next_state, recovery_event)) <<
        "Failed to perform entry action of state " << next_state <<
        " in transition from " << current_state_.load() << ".";
    }

    // Update only if the entry and exit actions were successful.
    current_state_.store(next_state);

    DVLOG(99)
      << "Changing current state to " << current_state_.load();

    RETURN_OK();
  }

  // Returns whether a given state-event pair results in a valid transition.
  MUST_USE_RETURN_VALUE
  ::basic::StatusOr<State> NextState(
    const State& from_state
    , const Event& event) const NO_EXCEPTION
  {
    // No transitions exist for this state.
    const auto transitions = table_.find(from_state);
    if (transitions == table_.end()) {
      return ::basic::Status(
        FROM_HERE, ::basic::error::INTERNAL, "Invalid transition.");
    }

    // No transition from this state with the given event.
    const auto next_state_iter = transitions->second.find(event);
    if (next_state_iter == transitions->second.end()) {
      return ::basic::Status(
        FROM_HERE, ::basic::error::INTERNAL, "Invalid transition.");
    }

    // A valid transition was found; return the next state.
    return {next_state_iter->second};
  }

 private:
  /// \note Thread collision warner used only for modification operations
  /// because you may want to use unchangable storage
  /// that can be read from multiple threads safely.
  // Thread collision warner to ensure that API is not called concurrently.
  // API allowed to call from multiple threads, but not
  // concurrently.
  DFAKE_MUTEX(debug_thread_collision_warner_);

  // The current state of the StateMachine,
  // initialized in the constructor.
  std::atomic<State> current_state_;

  // A TransitionTable that stores valid transitions
  // from any given state.
  TransitionTable table_;

  // A vector of actions that are executed upon entry
  // to any given state.
  ::base::flat_map<State, std::vector<CallbackType>> entry_actions_;

  // A vector of actions that are executed upon exit
  // from any given state.
  ::base::flat_map<State, std::vector<CallbackType>> exit_actions_;
};

}  // namespace basic
