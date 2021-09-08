const preservedGlobalMojo = self && self.mojo;
(function(){'use strict';var aa="function"==typeof Object.defineProperties?Object.defineProperty:function(a,b,c){if(a==Array.prototype||a==Object.prototype)return a;a[b]=c.value;return a};function ba(a){a=["object"==typeof globalThis&&globalThis,a,"object"==typeof window&&window,"object"==typeof self&&self,"object"==typeof global&&global];for(var b=0;b<a.length;++b){var c=a[b];if(c&&c.Math==Math)return c}throw Error("Cannot find global object");}var ca=ba(this);
function da(a,b){if(b)a:{var c=ca;a=a.split(".");for(var e=0;e<a.length-1;e++){var d=a[e];if(!(d in c))break a;c=c[d]}a=a[a.length-1];e=c[a];b=b(e);b!=e&&null!=b&&aa(c,a,{configurable:!0,writable:!0,value:b})}}function ea(a){function b(e){return a.next(e)}function c(e){return a.throw(e)}return new Promise(function(e,d){function f(g){g.done?e(g.value):Promise.resolve(g.value).then(b,c).then(f,d)}f(a.next())})}
function fa(a,b){a instanceof String&&(a+="");var c=0,e=!1,d={next:function(){if(!e&&c<a.length){var f=c++;return{value:b(f,a[f]),done:!1}}e=!0;return{done:!0,value:void 0}}};d[Symbol.iterator]=function(){return d};return d}da("Array.prototype.values",function(a){return a?a:function(){return fa(this,function(b,c){return c})}});function h(a,b){a=a.split(".");let c=ha;for(let e;a.length&&(e=a.shift());)a.length||void 0===b?c[e]&&c[e]!=Object.prototype[e]?c=c[e]:c=c[e]={}:c[e]=b};var ha=self;h("mojo.internal.exportModule",function(a){let b=ha;a=a.split(".");for(let c;a.length&&(c=a.shift());)b[c]||(b[c]={}),b=b[c]});var k=!!(new Uint8Array((new Uint16Array([1])).buffer))[0];function m(a){return null===a||void 0===a}function n(a){return a+(8-a%8)%8}
function p(a,b,c){k?(a.setUint32(b,Number(BigInt(c)&BigInt(4294967295)),k),a.setUint32(b+4,Number(BigInt(c)>>BigInt(32)&BigInt(4294967295)),k)):(a.setUint32(b,Number(BigInt(c)>>BigInt(32)&BigInt(4294967295)),k),a.setUint32(b+4,Number(BigInt(c)&BigInt(4294967295)),k))}function q(a,b){let c;k?(c=a.getUint32(b,k),a=a.getUint32(b+4,k)):(c=a.getUint32(b+4,k),a=a.getUint32(b,k));return BigInt(a)<<BigInt(32)|BigInt(c)}
function ia(a,b){let c=a.K,e=0;for(const d of a.v)a=b[d.name],m(a)&&(a=d.defaultValue),null!==a&&(d.type.$.H?(a=d.type.$.H(a,d.R),c+=n(a.size),e+=a.J):d.type.$.ba&&e++);return{size:c,J:e}}function ja(a,b){return a.o===r?8+(b.length+7)>>3:8+b.length*a.o.$.j(!!a.C)}function v(a,b){var c=ja(a,b);if(!a.o.$.H)return c;for(let e of b)m(e)||(c+=n(a.o.$.H(e,!!a.C).size));return c}function w(a,b){b=n(b);const c=new DataView(a.buffer,a.g,b);a.g+=b;return c}
var la=class{constructor(a,b,c,e,d,f,g){const l=ia(f,g);let t,z;0<l.J?(t=48,z=2):0==(c&3)?(t=24,z=0):(t=32,z=1);const F=t+l.size,Ca=0<l.J?8+4*l.J:0;this.buffer=new ArrayBuffer(F+n(Ca));this.handles=[];const u=new DataView(this.buffer);u.setUint32(0,t,k);u.setUint32(4,z,k);u.setUint32(8,b,k);u.setUint32(12,e,k);u.setUint32(16,c,k);u.setUint32(20,0);1<=z&&(p(u,24,d),2<=z&&(p(u,32,BigInt(16)),p(u,40,BigInt(F-40)),u.setUint32(F,Ca,k),u.setUint32(F+4,l.J||0,k)));this.i=0;this.h=null;l.J&&(this.h=new Uint32Array(this.buffer,
F+8,l.J));this.g=t;b=w(this,f.K);ka(new x(this,b,{endpoint:a}),f,g)}};function ma(a){y||(y=new TextEncoder("utf-8"));return y.encode(a)}function ka(a,b,c){var e=b.oa;A(a,0,b.K);A(a,4,e[e.length-1].version);for(const d of b.v)if(e=8+d.ka,c&&!m(c[d.name]))d.type.$.encode(c[d.name],a,e,d.fa,d.R);else if(null!==d.defaultValue)d.type.$.encode(d.defaultValue,a,e,d.fa,d.R);else if(d.R)d.type.$.D(a,e);else throw Error(b.name+' missing value for non-nullable field "'+d.name+'"');}
function na(a,b,c,e){const d=a.u.getUint8(b);e?a.u.setUint8(b,d|1<<c):a.u.setUint8(b,d&~(1<<c))}function A(a,b,c){a.u.setUint32(b,c,k)}function oa(a,b,c){A(a,b,a.A.handles.length);a.A.handles.push(c)}function pa(a,b,c){console.assert(c.ca,"expected unbound associated endpoint");{var e=a.S.endpoint;console.assert(e.g,"cannot associate with unbound endpoint");const d=c.P;c.P=d.P=null;c=e.g;c=(c.ua++|c.ea)>>>0;d.g=e.g;d.i=c;d.h&&qa(e.g,d,c)}e=a.A.i++;A(a,b,e);a.A.h[e]=c}
function B(a,b,c,e){const d=ja(b,e),f=w(a.A,d),g=new x(a.A,f,a.S);C(a,c,f.byteOffset);A(g,0,d);A(g,4,e.length);a=8;if(b.o===r){b=0;for(const l of e)na(g,a,b,l),b++,8==b&&(b=0,a++)}else for(const l of e){if(null===l){if(!b.C)throw Error("Trying to send a null element in an array of non-nullable elements");b.o.$.D(g,a)}b.o.$.encode(l,g,a,0,!!b.C);a+=b.o.$.j(!!b.C)}}function C(a,b,c){p(a.u,b,c-a.u.byteOffset-b)}
function ra(a,b,c,e){let d,f;"Map"==e.constructor.name?(d=Array.from(e.keys()),f=Array.from(e.values())):(d=Object.keys(e),f=d.map(t=>e[t]));const g=w(a.A,24),l=new x(a.A,g,a.S);C(a,c,g.byteOffset);A(l,0,24);A(l,4,0);B(l,{o:b.da},8,d);B(l,{o:b.valueType,C:b.na},16,f)}
function sa(a,b,c,e){var d=Object.keys(e);if(1!==d.length)throw Error(`Value for ${b.name} must be an Object with a `+"single property named one of: "+Object.keys(b.v).join(","));d=d[0];b=b.v[d];A(a,c,16);A(a,c+4,b.ordinal);c+=8;if("undefined"!==typeof b.type.$.T){{b=b.type.$.T;e=e[d];d=w(a.A,16);const f=new x(a.A,d,a.S);C(a,c,d.byteOffset);sa(f,b,0,e)}}else b.type.$.encode(e[d],a,c,0,b.nullable)}var x=class{constructor(a,b,c=null){this.S=c;this.A=a;this.u=b}},y=null;
function D(a,b){return a.m.getUint32(b,k)}function ta(a,b){b=a.m.getUint32(b,k);if(4294967295==b)return null;if(b>=a.O.length)throw Error("Decoded invalid handle index");return a.O[b]}
function E(a,b,c){c=G(a,c);if(!c)return null;a=new H(new DataView(a.m.buffer,c),a.O,a.L);D(a,0);c=D(a,4);if(!c)return[];const e=[];if(b.o===r)for(var d=0;d<c;++d){b=e;var f=b.push;var g=d%8;g=!!(a.m.getUint8(8+(d>>3))&1<<g);f.call(b,g)}else for(f=8,d=0;d<c;++d){g=b.o.$.decode(a,f,0,!!b.C);if(null===g&&!b.C)throw Error("Received unexpected array element");e.push(g);f+=b.o.$.j(!!b.C)}return e}
function G(a,b){const c=q(a.m,b);if(0==c)return 0;if(c>BigInt(Number.MAX_SAFE_INTEGER))throw Error("Mesage offset too large");return a.m.byteOffset+b+Number(c)}
function I(a,b){var c=D(a,0);const e=D(a,4);a:{var d=b.oa;for(let f=d.length-1;0<=f;--f){const g=d[f];if(e>g.version){d=c>=g.K;break a}if(e==g.version){d=c==g.K;break a}}throw Error(`Impossible version ${e} for struct ${b.name}`);}if(!d)throw Error(`Received ${b.name} of invalid size (${c}) and/or `+`version (${e})`);c={};for(const f of b.v)if(d=8+f.ka,f.sa>e)c[f.name]=f.defaultValue;else{d=f.type.$.decode(a,d,f.fa,!!f.R);if(null===d&&!f.R)throw Error("Received "+b.name+' with invalid null field "'+
f.name+'"');c[f.name]=d}return c}function ua(a,b,c){if(0===D(a,c))return null;var e=D(a,c+4);for(const d in b.v){const f=b.v[d];if(f.ordinal===e){e=c+8;"undefined"!==typeof f.type.$.T?(c=f.type.$.T,a=(e=G(a,e))?ua(new H(new DataView(a.m.buffer,e),a.O,a.L),c,0):null):a=f.type.$.decode(a,e,0,f.nullable);if(null===a&&!f.nullable)throw Error(`Received ${b.name} with invalid null `+`field: ${f.name}`);b={};b[d]=a;return b}}}
function va(a,b){if(!a.L||!a.L.endpoint)throw Error("cannot deserialize associated endpoint without context");const c=a.L.endpoint;var e=new DataView(a.m.buffer);const d=Number(q(e,40)),f=e.getUint32(d+44,k);e=new Uint32Array(e.buffer,d+48,f);a=D(a,b);return new J(c.G,e[a])}var H=class{constructor(a,b,c=null){this.L=c;this.m=a;this.O=b}},wa=null,r={$:{encode:function(a,b,c,e){na(b,c,e,a)},decode:function(a,b,c){return!!(a.m.getUint8(b)&1<<c)},l:!0}};h("mojo.internal.Bool",r);
h("mojo.internal.Int8",{$:{encode:function(a,b,c){b.u.setInt8(c,a)},decode:function(a,b){return a.m.getInt8(b)},j:()=>1,l:!0}});var K={$:{encode:function(a,b,c){b.u.setUint8(c,a)},decode:function(a,b){return a.m.getUint8(b)},j:()=>1,l:!0}};h("mojo.internal.Uint8",K);h("mojo.internal.Int16",{$:{encode:function(a,b,c){b.u.setInt16(c,a,k)},decode:function(a,b){return a.m.getInt16(b,k)},j:()=>2,l:!0}});
h("mojo.internal.Uint16",{$:{encode:function(a,b,c){b.u.setUint16(c,a,k)},decode:function(a,b){return a.m.getUint16(b,k)},j:()=>2,l:!0}});h("mojo.internal.Int32",{$:{encode:function(a,b,c){b.u.setInt32(c,a,k)},decode:function(a,b){return a.m.getInt32(b,k)},j:()=>4,l:!0}});var L={$:{encode:function(a,b,c){A(b,c,a)},decode:function(a,b){return D(a,b)},j:()=>4,l:!0}};h("mojo.internal.Uint32",L);
var xa={$:{encode:function(a,b,c){b=b.u;k?(b.setUint32(c,Number(BigInt(a)&BigInt(4294967295)),k),b.setInt32(c+4,Number(BigInt(a)>>BigInt(32)&BigInt(4294967295)),k)):(b.setInt32(c,Number(BigInt(a)>>BigInt(32)&BigInt(4294967295)),k),b.setUint32(c+4,Number(BigInt(a)&BigInt(4294967295)),k))},decode:function(a,b){var c=a.m;k?(a=c.getUint32(b,k),b=c.getInt32(b+4,k)):(a=c.getUint32(b+4,k),b=c.getInt32(b,k));return b=BigInt(b)<<BigInt(32)|BigInt(a)},j:()=>8,l:!0}};h("mojo.internal.Int64",xa);
h("mojo.internal.Uint64",{$:{encode:function(a,b,c){p(b.u,c,a)},decode:function(a,b){return q(a.m,b)},j:()=>8,l:!0}});h("mojo.internal.Float",{$:{encode:function(a,b,c){b.u.setFloat32(c,a,k)},decode:function(a,b){return a.m.getFloat32(b,k)},j:()=>4,l:!0}});h("mojo.internal.Double",{$:{encode:function(a,b,c){b.u.setFloat64(c,a,k)},decode:function(a,b){return a.m.getFloat64(b,k)},j:()=>8,l:!0}});
var M={$:{encode:function(a,b,c){oa(b,c,a)},D:function(a,b){A(a,b,4294967295)},decode:function(a,b){return ta(a,b)},j:()=>4,l:!1}};h("mojo.internal.Handle",M);var ya={$:{encode:function(a,b,c){if("string"!==typeof a)throw Error("Unxpected non-string value for string field.");B(b,{o:K},c,ma(a))},D:function(){},decode:function(a,b){(a=E(a,{o:K},b))?(wa||(wa=new TextDecoder("utf-8")),a=wa.decode((new Uint8Array(a)).buffer)):a=null;return a},H:function(a){return{size:v({o:K},ma(a))}},j:()=>8,l:!0}};
h("mojo.internal.String",ya);function za(a,b){const c={o:a,C:b};return{$:{Da:c,encode:function(e,d,f){B(d,c,f,e)},D:function(){},decode:function(e,d){return E(e,c,d)},H:function(e){return{size:v(c,e)}},j:()=>8,l:!1}}}h("mojo.internal.Array",za);
h("mojo.internal.Map",function(a,b,c){const e={da:a,valueType:b,na:c};return{$:{Fa:e,encode:function(d,f,g){ra(f,e,g,d)},D:function(){},decode:function(d,f){if(f=G(d,f)){f=new H(new DataView(d.m.buffer,f),d.O,d.L);d=D(f,0);var g=D(f,4);if(24!=d||0!=g)throw Error("Received invalid map data");d=E(f,{o:e.da},8);f=E(f,{o:e.valueType,C:e.na},16);if(d.length!=f.length)throw Error("Received invalid map data");if(e.da.$.l){g={};for(var l=0;l<d.length;++l)g[d[l]]=f[l];d=g}else{g=new Map;for(l=0;l<d.length;++l)g.set(d[l],
f[l]);d=g}}else d=null;return d},H:function(d){const f="Map"==d.constructor.name?Array.from(d.keys()):Object.keys(d),g="Map"==d.constructor.name?Array.from(d.values()):f.map(l=>d[l]);return{size:24+v({o:a},f)+v({o:b,C:c},g)}},j:()=>8,l:!1}}});function Aa(){return{$:{encode:function(a,b,c){A(b,c,a)},decode:function(a,b){return a.m.getInt32(b,k)},j:()=>4,l:!0}}}h("mojo.internal.Enum",Aa);function N(a,b,c,e,d,f,g=0){return{name:a,ka:b,fa:c,type:e,defaultValue:d,R:f,sa:g}}
h("mojo.internal.StructField",N);function O(a,b,c,e){e=e.map(f=>({version:f[0],K:f[1]}));const d={name:b,K:e[e.length-1].K,v:c,oa:e};a.$={I:d,encode:function(f,g,l){{const t=w(g.A,d.K),z=new x(g.A,t,g.S);C(g,l,t.byteOffset);ka(z,d,f)}},D:function(){},decode:function(f,g){return f=(g=G(f,g))?I(new H(new DataView(f.m.buffer,g),f.O,f.L),d):null},H:function(f){return ia(d,f)},j:()=>8,l:!1}}h("mojo.internal.Struct",O);
h("mojo.internal.createStructDeserializer",function(a){return function(b){if(void 0==a.$||void 0==a.$.I)throw Error("Invalid struct mojom type!");return I(new H(b,[]),a.$.I)}});
function P(a,b,c){const e={name:b,v:c};a.$={T:e,encode:function(d,f,g){sa(f,e,g,d)},D:function(){},decode:function(d,f){return ua(d,e,f)},H:function(d,f){{f=f?16:0;let l=0;var g=Object.keys(d);if(1!==g.length)throw Error(`Value for ${e.name} must be an Object with a `+"single property named one of: "+Object.keys(e.v).join(","));const t=g[0];g=e.v[t];d=d[t];m(d)||(g.type.$.H?(d=g.type.$.H(d,!!g.type.$.T||g.nullable),f+=n(d.size),l+=d.J):g.type.$.ba&&l++);f={size:f,J:l}}return f},j:d=>d?8:16,l:!1}}
h("mojo.internal.Union",P);h("mojo.internal.InterfaceProxy",function(a){return{$:{encode:function(b,c,e){b=b.proxy.ma();console.assert(b,`unexpected null ${a.name}`);b=Ba(b);oa(c,e,b);A(c,e+4,0)},D:function(b,c){A(b,c,4294967295)},decode:function(b,c){{const e=ta(b,c);D(b,c+4);b=e?new a(e):null}return b},j:()=>8,l:!1}}});
h("mojo.internal.InterfaceRequest",function(a){return{$:{encode:function(b,c,e){if(!b.handle)throw Error("Unexpected null "+a.name);oa(c,e,Ba(b.handle))},D:function(b,c){A(b,c,4294967295)},decode:function(b,c){return b=(b=ta(b,c))?new a(Q(b)):null},j:()=>8,l:!1}}});
h("mojo.internal.AssociatedInterfaceProxy",function(a){return{$:{type:a,encode:function(b,c,e){console.assert(b.proxy.endpoint&&b.proxy.endpoint.ca,`expected ${a.name} to be associated and unbound`);pa(c,e,b.proxy.endpoint);A(c,e+4,0)},D:function(b,c){A(b,c,4294967295);A(b,c+4,0)},decode:function(b,c){return new a(va(b,c))},j:()=>{throw Error("Arrays of associated endpoints are not yet supported");},l:!1,ba:!0}}});
h("mojo.internal.AssociatedInterfaceRequest",function(a){return{$:{type:a,encode:function(b,c,e){console.assert(b.handle&&b.handle.ca,`expected ${a.name} to be associated and unbound`);pa(c,e,b.handle)},D:function(b,c){A(b,c,4294967295)},decode:function(b,c){return new a(va(b,c))},j:()=>{throw Error("Arrays of associated endpoints are not yet supported");},l:!1,ba:!0}}});h("mojo.interfaceControl.RUN_MESSAGE_ID",4294967295);h("mojo.interfaceControl.RUN_OR_CLOSE_PIPE_MESSAGE_ID",4294967294);var R={$:{}};h("mojo.interfaceControl.RunMessageParamsSpec",R);var Da={$:{}};h("mojo.interfaceControl.RunResponseMessageParamsSpec",Da);var Ea={$:{}};h("mojo.interfaceControl.QueryVersionSpec",Ea);var Fa={$:{}};h("mojo.interfaceControl.QueryVersionResultSpec",Fa);var Ga={$:{}};h("mojo.interfaceControl.FlushForTestingSpec",Ga);var Ha={$:{}};
h("mojo.interfaceControl.RunOrClosePipeMessageParamsSpec",Ha);var Ia={$:{}};h("mojo.interfaceControl.RequireVersionSpec",Ia);var Ja={$:{}};h("mojo.interfaceControl.EnableIdleTrackingSpec",Ja);var Ka={$:{}};h("mojo.interfaceControl.MessageAckSpec",Ka);var La={$:{}};h("mojo.interfaceControl.NotifyIdleSpec",La);var Ma={$:{}};h("mojo.interfaceControl.RunInputSpec",Ma);var Na={$:{}};h("mojo.interfaceControl.RunOutputSpec",Na);var Oa={$:{}};h("mojo.interfaceControl.RunOrClosePipeInputSpec",Oa);
O(R.$,"RunMessageParams",[N("input",0,0,Ma.$,null,!1)],[[0,24]]);O(Da.$,"RunResponseMessageParams",[N("output",0,0,Na.$,null,!0)],[[0,24]]);O(Ea.$,"QueryVersion",[],[[0,8]]);O(Fa.$,"QueryVersionResult",[N("version",0,0,L,0,!1)],[[0,16]]);O(Ga.$,"FlushForTesting",[],[[0,8]]);O(Ha.$,"RunOrClosePipeMessageParams",[N("input",0,0,Oa.$,null,!1)],[[0,24]]);O(Ia.$,"RequireVersion",[N("version",0,0,L,0,!1)],[[0,16]]);O(Ja.$,"EnableIdleTracking",[N("timeoutInMicroseconds",0,0,xa,BigInt(0),!1)],[[0,16]]);
O(Ka.$,"MessageAck",[],[[0,8]]);O(La.$,"NotifyIdle",[],[[0,8]]);P(Ma.$,"RunInput",{queryVersion:{ordinal:0,type:Ea.$},flushForTesting:{ordinal:1,type:Ga.$}});P(Na.$,"RunOutput",{queryVersionResult:{ordinal:0,type:Fa.$}});P(Oa.$,"RunOrClosePipeInput",{requireVersion:{ordinal:0,type:Ia.$},enableIdleTracking:{ordinal:1,type:Ja.$},messageAck:{ordinal:2,type:Ka.$},notifyIdle:{ordinal:3,type:La.$}});var Pa={$:Aa()};h("mojo.native.SerializedHandleTypeSpec",Pa);h("mojo.native.SerializedHandleType",{Aa:0,Ba:1,Ca:2,za:3,ya:4,MIN_VALUE:0,MAX_VALUE:4});var Qa={$:{}};h("mojo.native.SerializedHandleSpec",Qa);var Ra={$:{}};h("mojo.native.NativeStructSpec",Ra);O(Qa.$,"SerializedHandle",[N("theHandle",0,0,M,null,!1),N("type",4,0,Pa.$,0,!1)],[[0,16]]);O(Ra.$,"NativeStruct",[N("data",0,0,za(K,!1),null,!1),N("handles",8,0,za(Qa.$,!1),null,!0)],[[0,24]]);h("mojo.pipeControl.RUN_OR_CLOSE_PIPE_MESSAGE_ID",4294967294);var S={$:{}};h("mojo.pipeControl.RunOrClosePipeMessageParamsSpec",S);var Sa={$:{}};h("mojo.pipeControl.DisconnectReasonSpec",Sa);var Ta={$:{}};h("mojo.pipeControl.PeerAssociatedEndpointClosedEventSpec",Ta);var Ua={$:{}};h("mojo.pipeControl.PauseUntilFlushCompletesSpec",Ua);var Va={$:{}};h("mojo.pipeControl.FlushAsyncSpec",Va);var Wa={$:{}};h("mojo.pipeControl.RunOrClosePipeInputSpec",Wa);
O(S.$,"RunOrClosePipeMessageParams",[N("input",0,0,Wa.$,null,!1)],[[0,24]]);O(Sa.$,"DisconnectReason",[N("customReason",0,0,L,0,!1),N("description",8,0,ya,null,!1)],[[0,24]]);O(Ta.$,"PeerAssociatedEndpointClosedEvent",[N("id",0,0,L,0,!1),N("disconnectReason",8,0,Sa.$,null,!0)],[[0,24]]);O(Ua.$,"PauseUntilFlushCompletes",[N("flushPipe",0,0,M,null,!1)],[[0,16]]);O(Va.$,"FlushAsync",[N("flusherPipe",0,0,M,null,!1)],[[0,16]]);
P(Wa.$,"RunOrClosePipeInput",{peerAssociatedEndpointClosedEvent:{ordinal:0,type:Ta.$},pauseUntilFlushCompletes:{ordinal:1,type:Ua.$},flushAsync:{ordinal:2,type:Va.$}});function qa(a,b,c){0===c&&a.h.start();console.assert(null!==a.h.g,"adding a secondary endpoint with no primary");a.g.set(c,b)}
var $a=class{constructor(a,b){this.i=a;this.h=new Xa(a);this.h.s=this.wa.bind(this);this.h.i=this.s.bind(this);this.g=new Map;this.ua=1;this.ea=b?2147483648:0;this.G=new Ya(this,this.xa.bind(this))}get F(){return this.i}close(){console.assert(0===this.g.size,"closing primary endpoint with secondary endpoints still bound");var a=this.h;a.g&&Za(a);a.h.close()}wa(a,b){if(24>a.byteLength)console.error("Rejecting undersized message"),this.s();else{var c=new DataView(a);var e=c.getUint32(0,k),d=c.getUint32(4,
k);if(0==d&&24!=e||1==d&&32!=e||2<d)throw Error("Received invalid message header");c={Y:e,Ea:d,ja:c.getUint32(8,k),N:c.getUint32(12,k),flags:c.getUint32(16,k),requestId:1>d?0:c.getUint32(24,k)};e=this.G;4294967294!==c.N?e=!1:(d=new DataView(a,c.Y),d=I(new H(d,[]),S.$.$.I).input,d.hasOwnProperty("peerAssociatedEndpointClosedEvent")&&e.h(d.peerAssociatedEndpointClosedEvent.id),e=!0);if(!e)if(e=this.g.get(c.ja)){console.assert(e.h,"endpoint has no client");d=e.s;if(4294967295===c.N){var f=new DataView(a,
c.Y);const g=new H(f,[]);c.flags&1?(f=c.requestId,I(g,R.$.$.I).input.hasOwnProperty("flushForTesting")?(T(d.g,4294967295,f,2,Da.$,{output:null}),d=!0):d=!1):(d=d.h.get(c.requestId))?(d(),d=!0):d=!1}else d=!1;d||e.h.F(e,c,a,b)}else console.error(`Received message for unknown endpoint ${c.ja}`)}}s(){for(const a of this.g.values())a.h&&a.h.h(a);this.g.clear()}xa(a){(a=this.g.get(a))&&a.h&&a.h.h(a)}};function ab(){const a=new J,b=new J;b.P=a;a.P=b;return{ha:a,ia:b}}
function Ba(a){console.assert(a.isPrimary(),"secondary endpoint cannot release pipe");return a.g.F}function bb(a){const b=a.F++;4294967295<a.F&&(a.F=0);return b}function T(a,b,c,e,d,f){b=new la(a,a.i,e,b,c,d.$.I,f);console.assert(a.g,"cannot send message on unassociated unbound endpoint");a.g.i.writeMessage(b.buffer,b.handles)}function cb(a){if(a.g){var b=a.g,c=a.i;b.g.delete(c);0===c&&Za(b.h)}a.h=null;a.s=null}
var J=class{constructor(a=null,b=0){this.g=a;this.i=b;this.s=new db(this);this.h=null;this.F=0;this.P=null}get G(){return this.g}isPrimary(){return null!==this.g&&0===this.i}get ca(){return null!==this.P}start(a){console.assert(!this.h,"endpoint already started");this.h=a;this.g&&qa(this.g,this,this.i)}get ea(){return null!==this.h}close(){if(this.g){var a=this.G,b=this.i;a.g.delete(b);0===b&&Za(a.h);0===b?a.close():(a=a.G,b=new la(null,4294967295,0,4294967294,0,S.$.$.I,{input:{peerAssociatedEndpointClosedEvent:{id:b}}}),
a.g.i.writeMessage(b.buffer,b.handles))}this.s=this.h=null}M(){const a=this;return ea(function*(){return eb(a.s)}())}};function Q(a,b=!1){return"MojoHandle"!=a.constructor.name?a:new J(new $a(a,b),0)}h("mojo.internal.interfaceSupport.getEndpointForReceiver",function(a){return Q(a)});h("mojo.internal.interfaceSupport.bind",function(a,b,c){console.assert(a.isPrimary()&&null===a.g.h.g,"endpoint is either associated or already bound");Mojo.bindInterface(b,a.g.F,c)});
var Ya=class{constructor(a,b){this.g=a;this.h=b}};function eb(a){var b={flushForTesting:{}};const c=bb(a.g);return new Promise(e=>{T(a.g,4294967295,c,1,R.$,{input:b});a.h.set(c,e)})}var db=class{constructor(a){this.g=a;this.h=new Map}};function fb(a){for(const b of a.g.values())b()}var U=class{constructor(){this.g=new Map;this.h=0}addListener(a){const b=++this.h;this.g.set(b,a);return b}removeListener(a){return this.g.delete(a)}};h("mojo.internal.interfaceSupport.ConnectionErrorEventRouter",U);
U.prototype.removeListener=U.prototype.removeListener;U.prototype.addListener=U.prototype.addListener;h("mojo.internal.interfaceSupport.PendingReceiver",class{get handle(){}});function gb(a,b){a.g&&cb(a.g);for(const c of a.i.keys())a.i.get(c).reject(Error(b));a.i=new Map}
var V=class{constructor(a,b){this.g=null;this.G=a;this.i=new Map;this.s=new U;b&&this.B(b)}get endpoint(){return this.g}W(){let {handle0:a,handle1:b}=Mojo.createMessagePipe();this.B(a);return new this.G(Q(b))}B(a){console.assert(!this.g,"already bound");this.g=a=Q(a,!0);this.g.start(this);this.i=new Map}U(){console.assert(!this.g,"cannot associate when already bound");const {ha:a,ia:b}=ab();this.B(a);return new this.G(b)}ma(){if(!this.g)return null;const a=this.g;this.g=null;cb(a);return a}close(){gb(this,
"Message pipe closed.");this.g&&this.g.close();this.g=null}aa(){return this.s}va(a,b,c,e){if(c&&(!this.g||!this.g.ea))return Promise.reject(Error("The pipe has already been closed."));const d={};b.$.I.v.forEach((g,l)=>d[g.name]=e[l]);const f=bb(this.g);T(this.g,a,f,c?1:0,b,d);return c?new Promise((g,l)=>{this.i.set(f,{requestId:f,N:a,Z:c,resolve:g,reject:l})}):Promise.resolve()}M(){return this.g.M()}F(a,b,c,e){if(!(b.flags&2)||b.flags&1)this.h(a,"Received unexpected request message");else{var d=this.i.get(b.requestId);
this.i.delete(b.requestId);d?(c=I(new H(new DataView(c,b.Y),e,{endpoint:a}),d.Z.$.I))&&b.N===d.N?d.resolve(c):this.h(a,"Received malformed response message"):this.h(a,"Received unexpected response message")}}h(a,b){gb(this,b);fb(this.s)}};h("mojo.internal.interfaceSupport.InterfaceRemoteBase",V);V.prototype.flushForTesting=V.prototype.M;V.prototype.sendMessage=V.prototype.va;V.prototype.getConnectionErrorEventRouter=V.prototype.aa;V.prototype.close=V.prototype.close;V.prototype.unbind=V.prototype.ma;
V.prototype.associateAndPassReceiver=V.prototype.U;V.prototype.bindHandle=V.prototype.B;var W=class{constructor(a){this.g=a}W(){return this.g.W()}U(){return this.g.U()}ra(){return null!==this.g.g}close(){this.g.close()}M(){return this.g.M()}};h("mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper",W);W.prototype.flushForTesting=W.prototype.M;W.prototype.close=W.prototype.close;W.prototype.isBound=W.prototype.ra;W.prototype.associateAndPassReceiver=W.prototype.U;
W.prototype.bindNewPipeAndPassReceiver=W.prototype.W;var hb=class{constructor(){this.g=new Map;this.h=0}removeListener(a){this.g.get(a)();return this.g.delete(a)}};h("mojo.internal.interfaceSupport.CallbackRouter",hb);hb.prototype.removeListener=hb.prototype.removeListener;
var X=class{constructor(a){this.g=new Map;this.h=a}addListener(a){const b=++this.h.h;this.g.set(b,a);this.h.g.set(b,()=>this.g.delete(b));return b}pa(a){return a?this.i.bind(this):this.s.bind(this)}s(a){const b=Array.from(arguments);this.g.forEach(c=>c.apply(null,b))}i(a){const b=Array.from(arguments),c=Array.from(this.g.values()).map(d=>d.apply(null,b));let e;for(const d of c)if(void 0!==d){if(void 0!==e)throw Error("Multiple listeners attempted to reply to a message");e=d}return e}};
h("mojo.internal.interfaceSupport.InterfaceCallbackReceiver",X);X.prototype.createReceiverHandler=X.prototype.pa;X.prototype.addListener=X.prototype.addListener;
var Y=class{constructor(a){this.g=new Set;this.G=a;this.s=new Map;this.i=new U}ta(a,b,c,e){this.s.set(a,{la:b,Z:c,qa:e})}B(a){a=Q(a);this.g.add(a);a.start(this)}X(){let a=new this.G;this.B(a.$.W().handle);return a}V(){const {ha:a,ia:b}=ab();this.B(a);return new this.G(b)}ga(){for(const a of this.g)a.close();this.g.clear()}aa(){return this.i}flush(){const a=this;return ea(function*(){for(let b of a.g)yield b.M()}())}F(a,b,c,e){if(b.flags&2)throw Error("Received unexpected response on interface receiver");
const d=this.s.get(b.N);if(!d)throw Error("Received unknown message");const f=I(new H(new DataView(c,b.Y),e,{endpoint:a}),d.la.$.I);if(!f)throw Error("Received malformed message");c=d.qa.apply(null,d.la.$.I.v.map(g=>f[g.name]));if(d.Z){if(void 0===c)throw this.h(a),Error("Message expects a reply but its handler did not provide one.");if("object"!=typeof c||"Promise"!=c.constructor.name)c=Promise.resolve(c);c.then(g=>{T(a,b.N,b.requestId,2,d.Z,g)}).catch(()=>{this.h(a)})}}h(a){this.g.delete(a);a.close();
fb(this.i)}};h("mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal",Y);Y.prototype.flush=Y.prototype.flush;Y.prototype.getConnectionErrorEventRouter=Y.prototype.aa;Y.prototype.closeBindings=Y.prototype.ga;Y.prototype.associateAndPassRemote=Y.prototype.V;Y.prototype.bindNewPipeAndPassRemote=Y.prototype.X;Y.prototype.bindHandle=Y.prototype.B;Y.prototype.registerHandler=Y.prototype.ta;var Z=class{constructor(a){this.g=a}B(a){this.g.B(a)}X(){return this.g.X()}V(){return this.g.V()}close(){this.g.ga()}flush(){return this.g.flush()}};
h("mojo.internal.interfaceSupport.InterfaceReceiverHelper",Z);Z.prototype.flush=Z.prototype.flush;Z.prototype.close=Z.prototype.close;Z.prototype.associateAndPassRemote=Z.prototype.V;Z.prototype.bindNewPipeAndPassRemote=Z.prototype.X;Z.prototype.bindHandle=Z.prototype.B;function Za(a){a.g&&(a.g.cancel(),a.g=null)}
var Xa=class{constructor(a){this.h=a;this.s=null;this.i=()=>{};this.g=null}start(){this.g=this.h.watch({readable:!0},this.F.bind(this))}F(){for(;this.g;){const a=this.h.readMessage();if(a.result==Mojo.RESULT_SHOULD_WAIT)break;if(a.result==Mojo.RESULT_FAILED_PRECONDITION){this.i();break}if(a.result!=Mojo.RESULT_OK)throw Error("Unexpected error on HandleReader: "+a.result);this.s(a.buffer,a.handles)}}};}).call(this);
const mojoTmp = self['mojo'];
export {mojoTmp as mojo};
if (preservedGlobalMojo) {
  self.mojo = preservedGlobalMojo;
}
