(function() {
	if (!App)
		throw 'phoneex-js is needed.';

	var s = new App({
		namespace : 'p.s',
		shortened : 'phoneex-simple',
		name : 'PhoneEx Javascript Simple',
		version : new Version('1.0.0.0'),
		depends : {
			'p' : new Version('1.0.0.0')
		}
	});

	var ex = function(classname, method, id, params) {
		// debug('[NATIVE] ' + {classname: classname, method: method, id: id,
		// params: params}.jsonEncode());
		if (typeof androidHandler === 'function') {
			// log("androidHandler('" + classname + "','" + method+ "','" +id+
			// "','" + params +"');");
			androidHandler(classname, method, id, params);
		}
		;
	};

	var Batcher = {
		__queue__ : [],
		execute : function(classname, method, params, callback, scope,
				errorcallback) {

		}
	};

	var SClass = clazz(Class, {
		constructor : function() {
			Class.prototype.constructor.apply(this, arguments);
			this.id = this.id || p.generateId();
		},
		execute : function(classname, method, params, callback, scope,
				errorcallback) {

		}
	});

	var connector = {
		queue : [],
		exec : function(classname, method, params) {
			var parts = [].concat('external://', classname, '/', method);
			if (params) {
				if (typeof params === 'object') {
					parts = parts.concat('?args=', params.jsonEncode()
							.base64Encode());
				} else if (typeof params === 'string') {
					parts = parts.concat('?args=', params.base64Encode());
				}
			}
			this.queue.push(parts.join(''));
		},
		shift : function() {
			return this.queue.shift();
		}
	};

	var Component = clazz(SClass, {
		constructor : function() {
			this.id = this.id || p.generateId();
			// debug('[XCONSTRUCTOR] [' + this.xtype + '] [' + this.id + '] ' +
			// config.jsonEncode());
			Component.reg(this);
			if (this.initConfig)
				this.initConfig.apply(this, arguments);
			if (this.listeners)
				em.reg(this.listeners, this);
			if (this.items) {
				var children = [];
				this.items.each(function(item) {
					if (item.xtype)
						children.push(p.s.Component.create(item.xtype, item));
				});
				this.items = children;
			}
			;
			this.initialized = true;
			if (this.initMembers)
				this.initMembers.apply(this, arguments);
			if (this.items)
				this.items.each(function(item) {
					if (this.main && item.body)
						this.main.add(item.body);
				});
		},
		destroy : function() {
			Component.unreg(this);
		}
	});

	Component.__pool__ = {};

	Component.xtypes = {};

	Component.create = function(xtype, overrides) {
		overrides = overrides || xtype;
		if (overrides.initialized)
			return overrides;
		xtype = typeof xtype === 'string' ? xtype : overrides.xtype;
		if (xtype && Component.xtypes[xtype]) {
			var obj = typeof overrides === 'string' ? new Component.xtypes[xtype]()
					: new Component.xtypes[xtype](overrides);
			return obj;
		}
	};

	Component.extend = function(xtype, parent, overrides, defaults) {
		defaults = defaults || overrides || parent;
		overrides = overrides || parent || xtype;
		parent = parent || xtype;
		xtype = typeof xtype === 'string' ? xtype
				: (parent.xtype || overrides.xtype);
		parent = (typeof parent === 'function') ? parent : Component;
		var clz = clazz(parent, overrides, defaults);
		if (xtype) {
			Component.regXType(xtype, clz);
		}
		return clz;
	};

	Component.get = function(id) {
		return this.__pool__[id];
	}

	Component.reg = function(o) {
		p.generateId(o);
		Component.__pool__[o.id] = o;
	};

	Component.regXType = function(xtype, Class) {
		if (!Class && typeof xtype === 'function' && xtype.prototype.xtype) {
			Class = xtype;
			xtype = xtype.prototype.xtype;
		}
		this.xtypes[xtype] = Class;
	};

	Component.unreg = function(o) {
		if (o && o.id)
			delete Component.__pool__[o.id];
	}

	Component.unregXType = function(xtype) {
		delete Component.xtypes[xtype];
	};

	s.add({
		Class : SClass,
		Component : Component,
	});

	s.add(function() {
		apply(p.global, {
			SClass : SClass,
			XComponent : Component,
			external : ex
		});
	});

	s.install();
})();