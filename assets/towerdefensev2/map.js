var Map = clazz(TMXTiledMap, {
	mapFile : null,
	wayPoint : null,
	constructor : function() {
		this.callsuper();
		this.initWithTMXFile(this.mapFile);
		this.initWayPoint();
	},
	initWayPoint : function() {
		this.wayPoint = new Array();
		var group = this.objectGroupNamed("waypoint");
		var objects = group.getObjects();
		if (objects) {
			var x = 0;
			var y = 0;
			for ( var i = 0; i < objects.length; i++) {
				x = objects[i].getIntValue("x");
				y = objects[i].getIntValue("y");
				this.wayPoint[i] = new Point({
					x : x,
					y : y
				});
			}
		}
	}
});