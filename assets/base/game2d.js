/**
 * Provides basic JavaScript prototype features and utilities.
 * @class p
 * @singleton
 */
(function() {
	var global = this,
	objectProto = Object.prototype,
	objectConstructor = objectProto.constructor,
    toString = objectProto.toString,
	stringProto = String.prototype,
	arrayProto = Array.prototype,
	numberProto = Number.prtotype,
	funProto = Function.prototype,
	regProto = RegExp.prototype,
	dateProto = Date.prototype;
	
	funProto.clone = function() {
		if (this.toString().match(/[native code]/)) return this;
		eval('r=' + this);
		return r;
	};
	
	funProto.wrap = function(owner, property) {
		if (this.isClass) return this;
		var method = this.owner ? this.clone() : this;
		method.owner = owner;
		method.property = property;
		return method;
	};
	
	objectProto.override = function(overrides, isForce) {
		if (isForce) {
   		for (property in overrides)
   			if (overrides.hasOwnProperty(property))
   				this[property] = typeof (value = overrides[property]) === 'function' ? value.wrap(this, property) : value;
		} else {
   		for (property in overrides)
   			if (typeof this[property] !== 'undefined') continue;
   			else if (overrides.hasOwnProperty(property))
   				this[property] = typeof (value = overrides[property]) === 'function' ? value.wrap(this, property) : value;
		};
		return this;
	};
	
	funProto.override = function(overrides, isForce) {
		return objectProto.override.call(this, overrides, isForce);
	};
	
	objectProto.merge = function(merges, isForce) {
		if (isForce) {
	   		for (property in merges)
	   			this[property] = typeof (value = merges[property]) === 'function' ? value.wrap(this, property) : value;
		} else {
	   		for (property in merges)
	   			if (typeof this[property] !== 'undefined') continue;
	   			else this[property] = typeof (value = merges[property]) === 'function' ? value.wrap(this, property) : value;
		};
		return this;
	};
	
	funProto.merge = function(merges, isForce) {
		return objectProto.merge.call(this, merges, isForce);
	};
	
	function apply(object, config, defaults) {
		if (defaults) apply(object, defaults);
		return objectProto.override.call(object, config, true);
	};
	
	function applyIf(object, config, defaults) {
		if (defaults) applyIf(object, defaults);
		return objectProto.override.call(object, config);
	};
	
	objectProto.callsuper = function() {
		var method = arguments.callee.caller,
		args = method.arguments;
		if (!method.owner || !method.owner.clazz) return;
		var owner = method.owner.clazz,
			name = method.property;
		while(true) {
			if (!owner.superclass) return;
			owner = owner.superclass;
			method = owner.prototype[name];
			if (method && typeof method === 'function') return method.apply(this, arguments.length === 0 ? args || [] : arguments);
		};
	};
	
	function clazz(subclass, superclass, overrides) {
		var Class = function() {
			var current = this;
			while(!current.constructor || current.constructor === objectConstructor) {
				if (current.clazz && current.clazz.superclass)
					current = current.clazz.superclass.prototype;
				else break;
			};
			current.constructor.apply(this, arguments);
		};
		var className = false;
		Class.prototype.constructor = objectConstructor;
		if (typeof subclass === 'string') {
			className = subclass;
			subclass = Class;
		};
		if (!subclass) subclass = Class;
		if (isObject(subclass)) {
			overrides = subclass;
			superclass = undefined;
			subclass = Class;
		} else if ((!superclass && subclass != Class) || typeof superclass === 'object') {
			overrides = superclass;
			superclass = subclass;
			subclass = Class;
		};
		subclass.isClass = true;
		var subProto = subclass.prototype;
		subProto.clazz = subclass;
		if (superclass && superclass != subclass) {
			var	F = new Function(),
				superProto = superclass.prototype;
			F.prototype = superProto;
			subProto.merge(new F());
			subclass.superclass = superclass;
			if (superProto.constructor === objectConstructor && !superclass.isClass)
				superProto.constructor = superclass;
		};
		subProto.override(overrides, true);
		if (className) {
			var paths = className.split('.');
			className = paths.pop();
			var part = global;
			while(paths.length > 0) {
				var path = parts.shift();
				if (!part[path]) part[path] = {};
				part = part[path];
			};
			part[className] = subclass;
		};
		return subclass;
	};
	
	function namespace() {
		var i, ns, split, parts, path, paths, object = false;
		if ((ln = arguments.length) === 0) return global;
		for (i = 0; i < ln; i++) {
			ns = arguments[i];
			object = global;
			parts = ns.split('.');
			paths = [];
			for (var i = 0; i < parts.length; i++) {
				part = parts[i];
				paths.push('.', part);
				path = paths.slice(1).join('');
				if (!object[part])
					object[part] = new Object(path);
				object[part].__parent__ = object[part].__parent__ || object;
				object = object[part];
				object.namespace = object.namespace || path;
			};
		};
		return object;
	};
	
	function generateId(el, prefix) {
		if (el && el.id)
			return el.id;
		if (typeof el === 'string' && !prefix) {
			prefix = el;
			el = false;
		};
		prefix = prefix ? prefix : 'p-';
		if (!generateId.seeds[prefix]) generateId.seeds[prefix] = -1;
		var id = prefix + ++generateId.seeds[prefix];
		if (el) el.id = id;
		return id;
	};
	generateId.seeds = {};
	
	var Class = clazz({
		constructor:	function() {
			var config = arguments[0];
			if (arguments.length === 1 && typeof config === 'object')
				this.override(config, true);
		}
	});
	
	var Version = clazz(Class, {
		constructor:	function(major, minor, patch, build) {
							this.callsuper();
							var parts = typeof major === 'string' ? major.split('.') : [];
							this.override({
								major:	parts[0] || major || 0,
								minor:	parts[1] || minor || 0,
								patch:	parts[2] || patch || 0,
								build:	parts[3] || build || 0
							});
						},
		isNewer:		function(otherVersion) {
							if (!otherVersion) return true;
							if (otherVersion.major && this.major > otherVersion.major) return true;
							if (otherVersion.minor && this.minor > otherVersion.minor) return true;
							if (otherVersion.patch && this.patch > otherVersion.patch) return true;
							if (otherVersion.build && this.build > otherVersion.build) return true;
							return false;
						},
		toString:		function() {
							return 'ver ' + this.major + '.' + this.minor + '.' + this.patch + '.' + this.build; 
						}
	});
	
	var App = clazz(Class, {
		__objects__:	{},
		__functions__:	[],
		add:			function(key, value) {
							if (!key) return;
							if (!value) {
								switch (typeof key) {
								case 'object':
									this.__objects__.override(key, true);
									break;
								case 'function':
									this.__functions__.push(key);
									break;
								case 'array':
									for (var element in key)
										this.add(element);
									break;
								}
							} else this[key] = value;
							return this;
						},
		constructor:	function(shortened, version, namespace, name, description, depends) {
							this.callsuper();
							this.override({
								shortened:		shortened || generateId(),
								version:		version || new Version(),
								namespace:		namespace || shortened,
								name:			name || shortened,
								description:	description || name,
								depends:		depends || {}
							});
						},
		install:		function() {
							if (!this.__objects__) {
								return false;
							};
							for (var path in this.depends) {
								if (!this.depends.hasOwnProperty(path)) continue;
								var ver = this.depends[path],
									ns = namespace(path),
									app = ns.__app__;
								if (!app) return false;
								if (ver.isNewer(app.version)) return false;
							};
							var ns = namespace(this.namespace),
								exists = ns.__app__ || false;
							if (exists) {
								if (exists.isNewer(this)) {
									return false;
								} else if (!this.isNewer(exists)) {
									return false;
								};
							};
							ns.override(this.__objects__, true);
							ns.__app__ = this;
							delete this.__objects__;
							for (var i = 0; i < this.__functions__.length; i++)
								this.__functions__[i].call(ns);
							delete this.__functions__;
							return true;
						},
		isNewer:		function(other) {
							return this.version.isNewer(other.version);
						},
		toString:		function() {
							return this.name + ' ' + this.version;
						}
	});

	var p = new App({
		namespace:	'p',
		shortened:	'phoneex-js',
		name:		'PhoneEx Javascript Core',
		version:	new Version('1.0.0.0')
	}).add({
		App:			App,
		apply:			apply,
		applyIf:		applyIf,
		clazz:			clazz,
		Class:			Class,
		generateId:		generateId,
		global:			global,
		ns:				namespace,
		Version:		Version
	});
	
	function isArray(v) {
		return toString.apply(v) === '[object Array]';
	};
	
	function isBoolean(v) {
		return typeof v === 'boolean';
	};
	
	function isDate(v) {
		return toString.apply(v) === '[object Date]';
	};
	
	function isDefined(v) {
		return typeof v !== 'undefined';
	};
	
	function isElement(v) {
		return v ? !!v.tagName : false;
	};
	
	function isEmpty(value, allowBlank) {
		var isNull       = value == null,
			emptyArray   = (isArray(value) && !value.length),
			blankAllowed = !allowBlank ? value === '' : false;
		return isNull || emptyArray || blankAllowed;
	};
	
	function isFunction(v) {
		return toString.apply(v) === '[object Function]';
	};

	function isIterable(v) {
		if (!v) {
			return false;
		};
		if (isArray(v) || v.callee) {
			return true;
		};
		if ((type = toString.call(v)) === 'NodeList' || type === 'HTMLCollection') {
			return true;
		};
		return ((isDefined(v.nextNode) || v.item) && isNumber(v.length)) || false;
	};
	
	function isObject(v) {
		return !!v && !v.tagName && toString.call(v) === '[object Object]';
	};
	
	function isNumber(v) {
		return typeof v === 'number'
	};
	
	function isPrimitive(v) {
		return isBoolean(v) || isNumber(v) || isString(v);
	};
	
	function isRegExp(v) {
		return toString.apply(v) === '[object RegExp]';
	};
	
	function isString(v) {
		return typeof v === 'string';
	};
	
	function num(v, defaultValue) {
		v = Number(isEmpty(v) || isArray(v) || typeof v == 'boolean' || (typeof v == 'string' && v.trim().length == 0) ? NaN : v);
		return isNaN(v) ? defaultValue : v;
	};
	
	function valueFrom(value, defaultValue, allowBlank) {
		return isEmpty(value, allowBlank) ? defaultValue : value;
	};

	var lang = {
		isArray:		isArray,
		isBoolean:		isBoolean,
		isDate:			isDate,
		isDefined:		isDefined,
		isElement:		isElement,
		isEmpty:		isEmpty,
		isFunction:		isFunction,
		isIterable:		isIterable,
		isNumber:		isNumber,
		isObject:		isObject,
		isPrimitive:	isPrimitive,
		isRegExp:		isRegExp,
		isString:		isString,
		num:			num,
		valueFrom:		valueFrom
	};
	
	p.add({lang: lang});

	var Pattern = clazz({
		add:			function(pn, fn) {
							this.patterns.push({pn: pn, fn: fn});
							return this;
						},
		apply:			function() {
							args = arguments.length <= 1 ? arguments[0] : Array.prototype.slice.call(arguments);
							for (index = 0; index < this.patterns.length; index++) {
								pattern = this.patterns[index];
								if (result = Pattern.match(pattern.pn, args)) {
									pattern.fn.apply(result, []);
									break;
								};
							};
						},
		constructor:	function(patterns) {
							if (patterns) this.patterns = patterns;
						},
		patterns:		[]
	});
	
	Pattern.override({
		create:		function(patterns) {
						var body = new Pattern(patterns);
						return function() {
							body.apply(arguments);
						};
					},
		match:		function(src, dest) {
						if (src.size() !== dest.size()) return false;
						var result = {};
						for (var memberWithOperator in src) {
							if (!src.hasOwnProperty(memberWithOperator)) continue;
							var parts = memberWithOperator.match(/(.*)\$(.*)$/),
								member = parts ? parts[1] : memberWithOperator,
								operator = parts ? parts[2] : 'eq',
								srcValue = src[memberWithOperator],
								destValue = dest[member],
								destType = typeof destValue;
							if (!isDefined(srcValue) ||
								!Pattern.operators[operator](srcValue, destValue))
								return false;
							result[member] = destValue;
						};
						return result;
					},
		operators:	{
						'_':	function(src, dest) {
									return isDefined(dest);
								},
						eq:		function(src, dest) {
									if (typeof src !== typeof dest) return false;
									if (isPrimitive(src)) return src === dest;
									return src.isEqual ? src.isEqual(dest) : src.toString() === dest.toString();
								},
						neq:	function(src, dest) {
									return !this.eq(src, dest);
								},
						gt:		function(src, dest) {
									if (typeof src !== typeof dest) return false;
									if (isPrimitive(src)) return dest > src;
									return false;
								},
						ngt:	function(src, dest) {
									if (typeof src !== typeof dest) return false;
									if (isPrimitive(src)) return dest <= src;
									return false;
								},
						lt:		function(src, dest) {
									if (typeof src !== typeof dest) return false;
									if (isPrimitive(src)) return dest < src;
									return false;
								},
						nlt:	function(src, dest) {
									if (typeof src !== typeof dest) return false;
									if (isPrimitive(src)) return dest >= src;
									return false;
								},
						match:	function(src, dest) {
									if (isRegExp(src)) return src.test(dest);
									return false;
								}
					}
	});
	
	p.add({Pattern: Pattern});

	var cache = {
		idx:	[],
		memory:	{},
		alive:	10 * 60 * 1000,
		maxium:	1000,
		get:	function(k) {
					var	t = new Date().getTime(),
						idx = this.idx,
						memory = this.memory,
						times = idx.length - maxium,
						i;
					for (i = 0; i < idx.length; i++) {
						var e = idx[i];
						if (e.alive < t || times-- > 0) {
							delete memory[e.key];
						} else break;
					};
					idx.splice(0, i);
					var e = this.memory[k];
					if (e) {
						this.put(e.key, e.value);
						return e.value;
					};
				},
		put:	function(k, v) {
					var e = {key: k, alive: new Date().getTime() + this.alive, value: v},
						idx = this.idx,
						memory = this.memory;
					idx.push(e);
					idx.unique(true);
					memory[k] = e;
				}
	};
	
	var callbackManager = {
		__pool__:	{},
		apply:		function() {
						var id = arguments[0];
						if (!id) return;
						var e = this.__pool__[id];
						if (!e) return;
						arguments[0] = e.scope;
						Function.call.apply(e.fn, arguments);
						delete this.__pool__[id];
					},
		err:		function() {
						var id = arguments[0];
						if (!id) return;
						var e = this.__pool__[id];
						if (!e) return;
						arguments[0] = e.scope;
						if (e.errFn)
							Function.call.apply(e.errFn, arguments);
						else Function.call.apply(this.error, arguments);
						delete this.__pool__[id];
					},
		error:		function(e) {
						error(e.msg);
					},
		reg:		function(fn, errFn, scope) {
						if (!scope) {
							scope = errFn;
							errFn = false;
						};
						var id = generateId('callback-');
						this.__pool__[id] = {fn: fn, errFn: errFn, scope: scope};
						return id;
					}
	};
	
	var context = {
		memory:	{},
		get:	function(k) {
					return this.memory[k];
				},
		put:	function(k, v) {
					this.memory[k] = v;
				},
		remove:	function(k) {
					var v = this.memory[k];
					delete this.memory[k];
					return v;
				}
	};
	
	var eventManager = {
		handlers:	{},
		fire:		function(event) {
						if (!event || !event.type) return;
						var entries = this.handlers[event.type] || [];
						for (var i = 0; i < entries.length; i++) {
							var entry = entries[i];
							if (event.id && event.id !== entry.scope.id) continue;
							if (entry.listener.call(entry.scope, event)) break;
						};
					},
		reg:		function() {
						var scope, entry, current = this;
						if (isObject(arguments[0])) {
							scope = arguments[1];
							arguments[0].each(function(fn, type) {
								current.reg(type, fn, scope);
							});
						} else {
							var type = arguments[0],
								fn = arguments[1],
								scope = arguments[2],
								entry = {listener: fn, scope: scope},
								listeners = this.handlers[type];
							this.handlers[type] = (this.handlers[type] || []).concat(entry);
						};
					},
		unreg:		function(type, fn, scope) {
						var listeners = handlers[type],
							listener;
						if (!listeners) return;
						for (var i = 0; i < listeners.length; i++) {
							listener = listeners[i];
							if (listener.fn == fn && listener.scope == scope) {
								listeners.splice(i, 1);
								break;
							};
						};
					}
	};
	
	var vlogger = {
		TRACE:		0,
		DEBUG:		1,
		VERBOSE:	2,
		INFO:		3,
		WARN:		4,
		ERROR:		5,
		FATAL:		6,
		levels:		['trace',
		       		 'debug',
		       		 'verbose',
		       		 'info',
		       		 'warn',
		       		 'error',
		       		 'fatal'],
		log:		function(message, tag, level) {
						//level = level || tag;
						level = isNumber(level) ? this.levels[level] : level;
						if (this.level && this.levels.indexOf(level) < this.level) return;
						if (this.regex && !tag) return;
						if (this.regex && !tag.match(this.regex)) return;

						if ('console' in global) {
							if (!level || !(level in global.console)) {
								level = 'log';
							};
							message = '[' + level.toUpperCase() + ']' + (tag ? '[' + tag.toUpperCase() + '] ' : ' ') + message;
							global.console[level](message);
						};
					},
		trace:		function(message, tag) {
						this.log(message, tag, this.TRACE);
					},
		debug:		function(message, tag) {
						this.log(message, tag, this.DEBUG);
					},
		verbose:	function(message, tag) {
						this.log(message, tag, this.VERBOSE);
					},
		info:		function(message, tag) {
						this.log(message, tag, this.INFO);
					},
		warn:		function(message, tag) {
						this.log(message, tag, this.WARN);
					},
		error:		function(message, tag) {
						this.log(message, tag, this.ERROR);
					},
		fatal:		function(message, tag) {
						this.log(message, tag, this.FATAL);
					},
		setLevel:	function(level) {
						this.level = isNumber(level) ? level : this.levels.indexOf(level); 
					},
		setTagRegex:function(regex) {
						this.regex = regex;
					}
	};
	
	p.add({
		cache:				cache,
		callbackManager:	callbackManager,
		context:			context,
		eventManager:		eventManager,
		logger:				vlogger
	});
	
	function dump(object) {
		var result = isFunction(object) ? object + '\n' : '';
		for (var property in object) {
			if (!object.hasOwnProperty(property)) continue;
			var value = object[property];
			var type = typeof value;
			if (isObject(value) || isFunction(value)) {
				result += '(' + type + ')' + property + ': {\n' + dump(value) + '\n' + '};\n'; 
			} else {
				result = '(' + type + ')' + property + ':' + value + '\n';
			};
		};
		return result;
	};
	
	p.add({dump: dump});
	
	p.add(function() {
		apply(numberProto, {
			times:	function(fn, scope) {
						if (this <= 0) return 0;
						for (var i = 0; i < this; i++) {
							if (fn.call(scope || i, i, this) === false) return index;
						};
					}
		});
		
		apply(stringProto, {
			trim:	function() {
						return this.replace(/(^\s*)(\s*$)/g, '');
					},
			ltrim:	function() {
						return this.replace(/(^\s*)/g, '');
					},
			rtrim:	function() {
						return this.replace(/(\s*$)/g, '');
					}
		});

		apply(objectProto, {
			each:		function(fn, scope) {
							if (this.length === 0) {
								return 0;
							};
							for (var prop in this) {
								if (this.hasOwnProperty(prop)) {
									if (fn.call(scope || this, this[prop], prop, this) === false) {
										return prop;
									};
								};
							};
							return true;
						},
			isEqual:	function(other) {
							if (!isObject(other) ||
								this.size() !== other.size()) return false;
							for (var property in this) {
								if (this.hasOwnProperty(property)) {
									var otherProperty = other[property],
										thisProperty = this[property],
										thisType = typeof thisProperty,
										otherType = typeof otherProperty;
									if (!ifDefined(otherProperty) ||
										thisType !== otherType) return false;
									if (isPrimitive(thisProperty) && thisProperty !== otherProperty) return false;
									if (thisProperty.isEqual && !thisProperty.isEqual(otherProperty)) return false;
								};
							};
							return true;
						},
			load:		function(obj) {
							this.override(obj, true);
						},
			loadIf:		function(obj) {
							this.override(obj);
						},
			pluge:		function(prop) {
							var ret = {};
							this.each(function(v, k) {
								ret[k] = v;
							});
							return ret;
						},
			size:		function() {
							var count = 0;
							for (var property in this) {
								if (this.hasOwnProperty(property)) count++;
							};
							return count;
						},
			toArray:	function() {
							var result = [];
							this.each(function(v) {
								result.push(v);
							});
							return result;
						}
		});
		
		apply(arrayProto, {
			each:			function(fn, scope) {
								if (isEmpty(this, true)) {
									return 0;
								};
								for (var i = 0, len = this.length; i < len; i++) {
									if (fn.call(scope || this[i], this[i], i, this) === false) {
										return i;
									};
								};
								return true;
							},
			indexOf:		function(v, s) {
								if (!s) s = 0;
								for (var i = s; i < this.length; i++)
									if (this[i] === v) return i;
								return -1;
							},
			isEqual:		function(other) {
								if (!isArray(other) ||
									this.length !== other.length) return false;
								for (var index = 0; index < this.length; index++) {
									var otherMember = other[index],
										thisMember = this[index],
										thisType = typeof thisMember,
										otherType = typeof otherMember;
									if (!isDefined(otherMember) ||
										thisType !== otherType) return false;
									if (isPrimitive(thisMember) && thisMember !== otherMember) return false;
									if (thisMember.isEqual && !thisMember.isEqual(otherMember)) return false;
								};
								return true;
							},
			lastIndexOf:	function(v, e) {
								if (!e) e = this.length - 1;
								for (var i = e; i > -1; i--)
									if (this[i] === v) return i;
								return -1;
							},
			pluge:			function(prop) {
								var ret = [];
								this.each(function(v) {
									ret.push(v);
								});
								return ret;
							},
			remove:			function(o) {
								var i = this.indexOf(o);
								if (i > -1) {
									this.splice(i, 1);
								}
							},
			unique:			function(f) {
								if (f) {
									for (var i = 0; i < this.length; i++)
										if (this.indexOf(this[i], i + 1))
											this.splice(i, 1);
									return this;
								} else {
									for (var i = this.length - 1; i > -1; i--)
										if (this.lastIndexOf(this[i], i - 1))
											this.splice(i, 1);
									return this;
								};
							}
		});
	}).add(function() {
		apply(stringProto, {
			urlAppend:	function(s) {
							var url = this,
								starter = url.indexOf('?') === -1 ? '?' : '&';
							if (!isEmpty(s)) {
								if (isString(s))
									return url + starter + s;
								else if (isObject(s))
									return url + starter + s.urlEncode();
							};
							return url;
						},
			urlDecode:	function(overwrite) {
							if (isEmpty(this)) {
								return {};
							};
							var obj = {},
								pairs = this.split(/[&?]/),
								d = decodeURIComponent,
								name,
								value;
							pairs.each(function(pair) {
								pair = pair.split('=');
								if (pair.length !== 0) {
									name = d(pair[0]);
									value = d(pair[1]);
									obj[name] = overwrite || !obj[name] ? value : [].concat(obj[name], value);
								};
							});
							return obj;
						}
		});
		
		apply(objectProto, {
			urlEncode:	function(pre) {
							var r = [],
								e = encodeURIComponent;
							this.each(function(v, k) {
								[].concat(v).each(function(vv) {
									r.push('&', e(k), '=', e(vv));
								});
							});
							if(!pre){
								r.shift();
								pre = '';
							};
							return pre + r.join('');
						}
		});
	});
	
	p.add(function() {
		apply(global, {
			App:		App,
			apply:		apply,
			applyIf:	applyIf,
			clazz:		clazz,
			Class:		Class,
			cm:			callbackManager,
			dump:		dump,
			em:			eventManager,
			logger:		vlogger,
			ns: 		namespace,
			Pattern:	Pattern,
			Version:	Version
		});
		
		applyIf(global, logger);
	});
	
	p.add(function() {
	    function f(n) {
	        return n < 10 ? '0' + n : n;
	    };
	
	    if (typeof Date.prototype.toJSON !== 'function') {
	
	        Date.prototype.toJSON = function (key) {
	
	            return isFinite(this.valueOf())
	                ? this.getUTCFullYear()     + '-' +
	                    f(this.getUTCMonth() + 1) + '-' +
	                    f(this.getUTCDate())      + 'T' +
	                    f(this.getUTCHours())     + ':' +
	                    f(this.getUTCMinutes())   + ':' +
	                    f(this.getUTCSeconds())   + 'Z'
	                : null;
	        };
	
	        String.prototype.toJSON =
	            Number.prototype.toJSON =
	            Boolean.prototype.toJSON = function (key) {
	                return this.valueOf();
	            };
	    };
	
	    var cx = /[\u0000\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,
	        escapable = /[\\\"\x00-\x1f\x7f-\x9f\u00ad\u0600-\u0604\u070f\u17b4\u17b5\u200c-\u200f\u2028-\u202f\u2060-\u206f\ufeff\ufff0-\uffff]/g,
	        gap,
	        indent,
	        meta = {    // table of character substitutions
	            '\b': '\\b',
	            '\t': '\\t',
	            '\n': '\\n',
	            '\f': '\\f',
	            '\r': '\\r',
	            '"' : '\\"',
	            '\\': '\\\\'
	        },
	        rep;
	    function quote(string) {
	        escapable.lastIndex = 0;
	        return escapable.test(string) ? '"' + string.replace(escapable, function (a) {
	            var c = meta[a];
	            return typeof c === 'string'
	                ? c
	                : '\\u' + ('0000' + a.charCodeAt(0).toString(16)).slice(-4);
	        }) + '"' : '"' + string + '"';
	    };
	
	    function str(key, holder) {
	        var i,          // The loop counter.
	            k,          // The member key.
	            v,          // The member value.
	            length,
	            mind = gap,
	            partial,
	            value = holder[key];
	        if (value && typeof value === 'object' &&
	                typeof value.toJSON === 'function') {
	            value = value.toJSON(key);
	        };
	        if (typeof rep === 'function') {
	            value = rep.call(holder, key, value);
	        };
	        switch (typeof value) {
	        case 'string':
	            return quote(value);
	
	        case 'number':
	            return isFinite(value) ? String(value) : 'null';
	
	        case 'boolean':
	        case 'null':
	            return String(value);
	        case 'object':

	            if (!value) {
	                return 'null';
	            };
	            gap += indent;
	            partial = [];
	            if (Object.prototype.toString.apply(value) === '[object Array]') {
	                length = value.length;
	                for (i = 0; i < length; i += 1) {
	                    partial[i] = str(i, value) || 'null';
	                };
	                v = partial.length === 0
	                    ? '[]'
	                    : gap
	                    ? '[\n' + gap + partial.join(',\n' + gap) + '\n' + mind + ']'
	                    : '[' + partial.join(',') + ']';
	                gap = mind;
	                return v;
	            };
	            if (rep && typeof rep === 'object') {
	                length = rep.length;
	                for (i = 0; i < length; i += 1) {
	                    if (typeof rep[i] === 'string') {
	                        k = rep[i];
	                        v = str(k, value);
	                        if (v) {
	                            partial.push(quote(k) + (gap ? ': ' : ':') + v);
	                        };
	                    };
	                };
	            } else {
	                for (k in value) {
	                    if (Object.prototype.hasOwnProperty.call(value, k)) {
	                        v = str(k, value);
	                        if (v) {
	                            partial.push(quote(k) + (gap ? ': ' : ':') + v);
	                        };
	                    };
	                };
	            };
	            v = partial.length === 0
	                ? '{}'
	                : gap
	                ? '{\n' + gap + partial.join(',\n' + gap) + '\n' + mind + '}'
	                : '{' + partial.join(',') + '}';
	            gap = mind;
	            return v;
	        };
	    };
	    
	    function jsonEncode(replacer, space) {
	        var i;
	        gap = '';
	        indent = '';
	        if (typeof space === 'number') {
	            for (i = 0; i < space; i += 1) {
	                indent += ' ';
	            };
	        } else if (typeof space === 'string') {
	            indent = space;
	        };
	        rep = replacer;
	        if (replacer && typeof replacer !== 'function' &&
	                (typeof replacer !== 'object' ||
	                typeof replacer.length !== 'number')) {
	            throw new Error('JSON.stringify');
	        };
	        return str('', {'': this});
	    };
	    
	    function jsonDecode(reviver) {
            var j;

            function walk(holder, key) {
                var k, v, value = holder[key];
                if (value && typeof value === 'object') {
                    for (k in value) {
                        if (Object.prototype.hasOwnProperty.call(value, k)) {
                            v = walk(value, k);
                            if (!isDefined(v)) {
                                value[k] = v;
                            } else {
                                delete value[k];
                            };
                        };
                    };
                };
                return reviver.call(holder, key, value);
            };
            text = this;
            cx.lastIndex = 0;
            if (cx.test(text)) {
                text = text.replace(cx, function (a) {
                    return '\\u' +
                        ('0000' + a.charCodeAt(0).toString(16)).slice(-4);
                });
            };
            if (/^[\],:{}\s]*$/
                    .test(text.replace(/\\(?:["\\\/bfnrt]|u[0-9a-fA-F]{4})/g, '@')
                        .replace(/"[^"\\\n\r]*"|true|false|null|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?/g, ']')
                        .replace(/(?:^|:|,)(?:\s*\[)+/g, ''))) {
                j = eval('(' + text + ')');
                return typeof reviver === 'function'
                    ? walk({'': j}, '')
                    : j;
            };
            throw new SyntaxError('JSON.parse');
        };
	    objectProto.jsonEncode = jsonEncode;
	    stringProto.jsonDecode = jsonDecode;
	});
	
	p.add(function() {
		utf8Ranges = [0x7F, 0x7FF, 0xFFFF, 0x1FFFFF, 0x3FFFFFF, 0x7FFFFFFF];
		utf8Heads = [0x0, 0x6 << 5, 0xE << 4, 0x1E << 3, 0x3E << 2, 0x7E << 1];
		utf8HeadOffsets = [7, 5, 4, 3, 2, 1];
		utf8Body = 0x2 << 6;
		utf8HeadMasks = [0x7F, 0x1F, 0xF, 0x7, 0x3, 0x1];
		utf8BodyMask = 0x3F;
		utf8BodySize = 6;
		byteSize = 8;
		maxByte = 0xFF;
		unicodeRanges = [0xFF, 0xFFFF, 0xFFFFFF, 0xFFFFFFFF, 0xFFFFFFFFFF, 0xFFFFFFFFFFFF];
		base64Chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghiklmnopqrstuvwxyz0123456789+/=';
		base64CharParts = base64Chars.split('');
		base64CharMaps = {};
		base64CharParts.each(function(value, index) {base64CharMaps[value] = index});
		
		function unicodeToUtf8(string) {
			result = [];
			for (i = 0; i < string.length; i++) {
				utf8 = 0;
				unicode = string.charCodeAt(i);
				for (index = 0; index < utf8Ranges.length; index++) {
					if (unicode > (range = utf8Ranges[index])) continue;
					head = utf8Heads[index];
					headMask = utf8HeadMasks[index];
					utf8 = (head + (unicode >> index * utf8BodySize)) << index * byteSize;
					unicode -= unicode & (headMask << index * utf8BodySize);
					while(--index >= 0) {
						utf8 += (utf8Body + (unicode >> index * utf8BodySize)) << index * byteSize;
						unicode -= unicode & (utf8BodyMask << index * utf8BodySize);
					};
					break;
				};
				result.push(utf8);
			};
			return result;
		};
		
		function unicodeToBinary(string) {
			result = [];
			for (i = 0; i < string.length; i++) {
				unicode = string.charCodeAt(i);
				result.push(unicode >> 16);
				result.push(unicode & maxByte);
			};
			return result;
		};
		
		function utf8ToBinary(utf8) {
			binary = [];
			for (i = 0; i < utf8.length; i++) {
				bytes = temp = 0;
				while((c = utf8[i]) > (temp += maxByte << bytes++ * byteSize));
				while(--bytes >= 0) {
					offset = bytes * byteSize;
					current = c & (maxByte << offset);
					binary.push(current >> offset);
					c -= current;
				};
			};
			return binary;
		};
		
		function binaryToBase64(binary) {
			offset = 0;
			base64 = [];
			eof = -1;
			while(eof === -1) {
				if (!(c1 = binary[offset++])) break;
				if (!(c2 = binary[offset++])) eof = 1;
				else if (!(c3 = binary[offset++])) eof = 2;
				c2 = c2 || 0;
				c3 = c3 || 0;
				c = (c1 << 16) + ((c2 || 0) << 8) + c3;
				base64.push(base64CharParts[(c & 0xFC0000) >> 18]);
				base64.push(base64CharParts[(c & 0x3F000) >> 12]);
				base64.push(eof > 0 ? '=' : base64CharParts[(c & 0xFC0) >> 6]);
				base64.push(eof > 1 ? '=' : base64CharParts[c & 0x3F]);
			};
			return base64.join('');
		};
		
		function base64ToBinary(base64) {
			 offset = 0;
			 binary = [];
			 eof = 0;
			 while(offset < base64.length) {
				base64Char1 = base64CharMaps[base64.charAt(offset++)];
				base64Char2 = base64CharMaps[base64.charAt(offset++)];
				base64Char3 = base64CharMaps[base64.charAt(offset++)];
				base64Char4 = base64CharMaps[base64.charAt(offset++)];
				if (base64Char3 === 64) {
					base64Char3 = base64Char4 = 0;
					eof = 2;
				} else if (base64Char4 === 64) {
					base64Char4 = 0;
					eof = 1;
				};
				c = ((base64Char1 & 0x3F) << 18) + ((base64Char2 & 0x3F) << 12) + ((base64Char3 & 0x3F) << 6) + base64Char4;
				binary.push((c & 0xFF0000) >> 16);
				if (eof < 2) binary.push((c & 0xFF00) >> 8);
				if (eof < 1) binary.push(c & 0xFF);
			 };
			 return binary;
		};
		
		function binaryToUtf8(binary) {
			result = [];
			offset = 0;
			while(offset < binary.length) {
				utf8 = bytes = index = 0;
				head = binary[offset];
				while((head >> (headOffset = utf8HeadOffsets[bytes])) !== (utf8Heads[bytes++] >> headOffset));
				while(index < bytes)
					utf8 += binary[offset++] << (bytes - ++index) * byteSize;
				result.push(utf8);
			};
			return result;
		};
		
		function binaryToUnicode(binary) {
			result = [];
			offset = 0;
			while(offset < binary.length) {
				c1 = binary[offset++];
				c2 = binary[offset++];
				if (c2) result.push((c1 << 16) + c2);
				else result.push(c1);
			}
		};
		
		function utf8ToUnicode(utf8Array) {
			result = [];
			offset = 0;
			while(offset < utf8Array.length) {
				unicode = 0;
				utf8 = utf8Array[offset++];
				for (index = 0; index < unicodeRanges.length; index++) {
					if (utf8 > (range = unicodeRanges[index])) continue;
					head = utf8Heads[index];
					headMask = utf8HeadMasks[index];
					unicode = ((utf8 >> index * byteSize) - head) << index * utf8BodySize;
					utf8 -= utf8 & (maxByte << index * byteSize);
					while(--index >= 0) {
						unicode += ((utf8 >> index * byteSize) - utf8Body) << index * utf8BodySize;
						utf8 -= utf8 & (maxByte << index * byteSize);
					};
					break;
				};
				result.push(unicode);
			};
			return String.fromCharCode.apply(String, result);
		};
		
		stringProto.base64Encode = function() {
			utf8 = unicodeToUtf8(this);
			binary = utf8ToBinary(utf8);
			return binaryToBase64(binary);
		};
		
		stringProto.base64Decode = function() {
			binary = base64ToBinary(this);
			utf8 = binaryToUtf8(binary);
			return utf8ToUnicode(utf8);
		};
	});
	
	p.install();
	
	return exports = p;
}) ();
