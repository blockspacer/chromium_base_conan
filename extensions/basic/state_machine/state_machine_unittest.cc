#include "basic/state_machine/state_machine.h" // IWYU pragma: associated
#include "basic/status/status_macros.h"
#include "basic/status/app_error_space.h"
#include "basic/annotations/guard_annotations.h"
#include "basic/macros.h"

#include "base/logging.h"
#include "base/test/task_environment.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace basic {

// MOTIVATION
//
// Prohibit invalid state transitions
// (like pausing from uninitialized state)
class ExampleStateMachine
{
public:
  enum State {
    // A possible initial state where the application can be running,
    // loading data, and so on, but is not visible to the user.
    UNINITIALIZED = 0,
    // The state where the application is running in the foreground,
    // fully visible, with all necessary resources available.
    // A possible initial state, where loading happens
    // while in the foreground.
    STARTED = 1,
    // The application is expected to be able to move back into
    // the Started state very quickly
    PAUSED = 2,
    // The application was running at some point,
    // but has been backgrounded to the
    // point where resources are invalid
    // and execution should be halted
    // until resumption.
    SUSPENDED = 3, /// \todo use it
    // Representation of a idle/terminal/shutdown state
    // with no resources.
    TERMINATED = 4,
    // Resources are invalid.
    FAILED = 5,
  };

  enum Event {
    START = 0,
    PAUSE = 1,
    SUSPEND = 2,
    TERMINATE = 3,
    FAULT = 4,
  };

  using StateMachineType =
      ::basic::StateMachine<
        ExampleStateMachine::State
        , ExampleStateMachine::Event
      >;

public:
  // USAGE
  //
  // // Warning: all callbacks must be used
  // // within the lifetime of the state machine.
  // StateMachineType::CallbackType okStateCallback =
  //   ::base::BindRepeating(
  //   []
  //   (Event event
  //    , State next_state
  //    , Event* recovery_event)
  //   {
  //     UNREFERENCED_PARAMETER(event);
  //     UNREFERENCED_PARAMETER(next_state);
  //     UNREFERENCED_PARAMETER(recovery_event);
  //     RETURN_OK();
  //   });
  // sm_->AddExitAction(UNINITIALIZED, okStateCallback);
  void AddExitAction(
   const State& state
   , const StateMachineType::CallbackType& callback) NO_EXCEPTION
  {
    sm_.AddExitAction(state, callback);
  }

  void AddEntryAction(
   const State& state
   , const StateMachineType::CallbackType& callback) NO_EXCEPTION
  {
    sm_.AddEntryAction(state, callback);
  }

  ExampleStateMachine(const State& initial_state = UNINITIALIZED);

  ExampleStateMachine(
    ExampleStateMachine&& other) = delete;

  ~ExampleStateMachine();

  MUST_USE_RETURN_VALUE
  State currentState()
  {
    return sm_.currentState();
  }

  MUST_USE_RETURN_VALUE
  ::basic::Status processStateChange(
    const ::base::Location& from_here
    , const ExampleStateMachine::Event& processEvent) NO_EXCEPTION;

private:

  // Defines all valid transitions for the state machine.
  // The transition table represents the following state diagram:
  /**
   * ASCII diagram generated using asciiflow.com
          +-------------------+----------------+----------------+----------------+
          ^                   ^                ^                ^                |
          |                   |     START      |                |                |
          |                   |   +---------+  |                |                |
          |                   |   |         |  |                |                |
          |                   +   v         +  |                +                v
     UNINITIALIZED         STARTED         PAUSED          TERMINATED         FAILED
        +   +              ^  +  +          ^  +             ^   ^  ^
        |   |              |  |  |          |  |             |   |  |
        |   +---------------  +  +----------+  +-------------+   |  |
        |         START       |      PAUSE           TERMINATE   |  |
        |                     |                                  |  |
        |                     |                                  |  |
        |                     |                                  |  |
        |                     |                                  |  |
        |                     +----------------------------------+  |
        |                                   TERMINATE               |
        +-----------------------------------------------------------+
                                  TERMINATE
  **/
  MUST_USE_RETURN_VALUE
  StateMachineType::TransitionTable fillStateTransitionTable();

private:
  StateMachineType sm_;

  // check sequence on which class was constructed/destructed/configured
  SEQUENCE_CHECKER(sequence_checker_);

  DISALLOW_COPY_AND_ASSIGN(ExampleStateMachine);
};


ExampleStateMachine::ExampleStateMachine(const State& initial_state)
  : sm_(initial_state, fillStateTransitionTable())
{
  LOG_CALL(DVLOG(99));

  DETACH_FROM_SEQUENCE(sequence_checker_);
}

basic::Status ExampleStateMachine::processStateChange(
  const ::base::Location &from_here
  , const ExampleStateMachine::Event &processEvent) NO_EXCEPTION
{
  LOG_CALL(DVLOG(99));

  DCHECK_RUN_ON(&sequence_checker_);

  const ::basic::Status stateProcessed
      = sm_.ProcessEvent(processEvent
                         , FROM_HERE.ToString()
                         , nullptr);
  if(!stateProcessed.ok())
  {
    LOG(WARNING)
      << "Failed to change state"
      << " using event "
      << processEvent
      << " in code "
      << from_here.ToString()
      << ". Current state: "
      << sm_.currentState();
  }
  return stateProcessed;
}

ExampleStateMachine::StateMachineType::TransitionTable
  ExampleStateMachine::fillStateTransitionTable()
{
  LOG_CALL(DVLOG(99));

  StateMachineType::TransitionTable sm_table_;

  // [state][event] -> next state
  sm_table_[UNINITIALIZED][START] = STARTED;
  sm_table_[UNINITIALIZED][TERMINATE] = TERMINATED;
  sm_table_[UNINITIALIZED][FAULT] = FAILED;

  sm_table_[STARTED][PAUSE] = PAUSED;
  sm_table_[STARTED][TERMINATE] = TERMINATED;
  sm_table_[STARTED][FAULT] = FAILED;

  sm_table_[PAUSED][TERMINATE] = TERMINATED;
  sm_table_[PAUSED][FAULT] = FAILED;

  sm_table_[TERMINATED][TERMINATE] = TERMINATED;
  sm_table_[TERMINATED][FAULT] = FAILED;

  sm_table_[FAILED][FAULT] = FAILED;

  return sm_table_;
}

ExampleStateMachine::~ExampleStateMachine()
{
  LOG_CALL(DVLOG(99));

  DCHECK_RUN_ON(&sequence_checker_);
}

class StateMachineTest : public testing::Test {
 public:
  StateMachineTest() = default;
  void SetUp() override {
  }

 protected:
  base::test::TaskEnvironment task_environment;
};

TEST_F(StateMachineTest, SimpleTest) {
  ExampleStateMachine example_sm(ExampleStateMachine::UNINITIALIZED);

  // UNINITIALIZED -> STARTED
  EXPECT_TRUE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::START).ok());

  // STARTED -> STARTED
  EXPECT_FALSE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::START).ok());

  // STARTED -> PAUSED
  EXPECT_TRUE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::PAUSE).ok());

  // PAUSED -> PAUSED
  EXPECT_FALSE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::PAUSE).ok());

  // PAUSED -> TERMINATED
  EXPECT_TRUE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::TERMINATE).ok());

  // TERMINATED -> STARTED
  EXPECT_FALSE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::START).ok());

  // TERMINATED -> FAILED
  EXPECT_TRUE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::FAULT).ok());

  // FAILED -> FAILED
  EXPECT_TRUE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::FAULT).ok());

  // FAILED -> FAILED
  EXPECT_TRUE(example_sm.processStateChange(FROM_HERE, ExampleStateMachine::FAULT).ok());

}

} // namespace basic
