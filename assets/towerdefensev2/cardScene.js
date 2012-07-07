var globalData = {
	monsters : null,
	wayPoint : null
};
var CardLayer = clazz(Layer, {
	map : null,
	tower : null,
	mapSizeHeight : 0,
	mapSizeWidth : 0,
	tileSizeHeight : 0,
	tileSizeWidth : 0,
	touchBeginPosistion : null,
	screen : null,
	scoreLabel : null,
	totoalScore : 0,
	constructor : function() {
		this.callsuper();
		this.loadMap();
		this.getMapWapPoint();
		this.createTower();
		this.setIsTouchEnabled(true);
		this.onTouchMoved(this.touchMovedEvent);
		globalData.monsters = new Array();
		this.totoalScore = 0;
		this.schedule(this.createMonster, 3);
		this.schedule(this.checkMonster, 0.3);
		var winSize = Application.getWinSize();
		this.screen = new Rect({
			x : 0,
			y : 0,
			width : winSize.width,
			height : winSize.height
		});
		this.createScoreLabel();
	},
	createScoreLabel : function() {
		var winWidth = this.screen.size.width;
		var winHeight = this.screen.size.height;
		var titlelabel = new LabelTTF({
			label : "score :",
			fontName : "Arial",
			fontSize : 60
		});
		this.scoreLabel = new LabelTTF({
			label : "0",
			fontName : "Arial",
			fontSize : 60
		});
		titlelabel.setPosition(winWidth - 50, winHeight - 30);
		this.scoreLabel.setPosition(winWidth - 20, winHeight - 30);
		this.addChild(this.scoreLabel, 4);
		this.addChild(titlelabel, 4);
	},
	convertToScreenPosition : function(x, y) {
		x = x * this.tileSizeWidth;
		y = (this.mapSizeHeight - y - 1) * this.tileSizeHeight
		return {
			x : x,
			y : y
		};
	},
	convertToMapPosition : function(x, y) {
		x = x / this.tileSizeWidth;
		y = (((this.mapSizeHeight - 1) * this.tileSizeHeight) - y)
				/ this.tileSizeHeight;
		return {
			x : x,
			y : y
		};
	},
	checkMonster : function(dt) {
		for ( var i = 0; i < globalData.monsters.length; i++) {
			var m = globalData.monsters[i];
			var pos = m.getPosition();
			var isContained = Rect.rectContainsPoint(this.screen, pos);
			if (m.curHp <= 0 || (!isContained && m.hasRun)) {
				if (m.curHp > 0) {
					this.totoalScore = this.totoalScore + m.score;
					this.scoreLabel.setString(this.totoalScore);
				} else {
					var b = new Blood();
					this.addChild(b, 3);
					b.show(pos.x, pos.y - 10);
				}
				globalData.monsters.splice(i, 1);
				m.unschedule(m.healthScheduleId);
				this.removeChild(m.healthBar, true);
				this.removeChild(m, true);
			}
		}
	},
	createMonster : function() {
		var m1 = new Monster();
		var healthBar = new HealthBar();
		healthBar.setPosition(-10, 0);
		m1.healthBar = healthBar;
		this.addChild(m1, 1);
		this.addChild(m1.healthBar, 3);
		m1.index = globalData.monsters.length;
		m1.move();
		globalData.monsters.push(m1);
	},
	touchMovedEvent : function(touch) {
		var curPos = touch.location();
		var prePos = touch.previousLocation();
		var diff = Point.sub(curPos, prePos);
		var self = this.getPosition();
		var nextPos = Point.add(self, diff);
		var mapContentSize = this.map.getContentSize();
		nextPos.x = Math.min(nextPos.x, 0);
		nextPos.x = Math.max(nextPos.x, screenWidth - mapContentSize.width);
		nextPos.y = Math.min(nextPos.y, 0);
		nextPos.y = Math.max(nextPos.y, screenHegiht - mapContentSize.height);
		this.setPosition(nextPos.x, nextPos.y);
	},
	mapContentSize : null,
	loadMap : function() {
		this.map = new TMXTiledMap({
			mapFile : 'map/map3.tmx'
		});
		var t = getScaleX();
		this.map.setScaleX(getScaleX());
		this.map.setScaleY(getScaleY());
		this.addChild(this.map, 0);
		this.mapContentSize = this.map.getContentSize();
		this.mapSizeHeight = this.map.getMapSize().height;
		this.mapSizeWidth = this.map.getMapSize().width;
		this.tileSizeHeight = this.map.getTileSize().height;
		this.tileSizeWidth = this.map.getTileSize().width;
	},
	createTower : function() {
		var group = this.map.objectGroupNamed("tower");
		var objects = group.getObjects();
		if (objects) {
			var x = 0;
			var y = 0;
			for ( var i = 0; i < objects.length; i++) {
				x = objects[i].getIntValue("x");
				y = objects[i].getIntValue("y");
				this.tower = new Tower();
				this.tower.setPosition(x, y);
				this.addChild(this.tower, 1);
			}
		}
	},
	getMapWapPoint : function() {
		globalData.wayPoint = new Array();
		var group = this.map.objectGroupNamed("waypoint");
		var objects = group.getObjects();
		if (objects) {
			var x = 0;
			var y = 0;
			for ( var i = 0; i < objects.length; i++) {
				x = objects[i].getIntValue("x");
				y = objects[i].getIntValue("y");
				globalData.wayPoint[i] = new Point({
					x : x,
					y : y
				});
			}
		}
	}
});

var CardScene = clazz(Scene, {
	constructor : function() {
		this.callsuper();
		this.addChild(new CardLayer());
		this.createMenu();
	},
	createMenu : function() {
		var menuItem = new MenuItemFont({
			title : "mainScene",
			handler : showsceneOne
		});
		menuItem.setPosition(screenWidth - 20, 20);
		var mainMenu = new Menu({
			item : menuItem
		});
		mainMenu.setPosition(0, 0);
		this.controlPanel().addChild(mainMenu, 1);
	},
});

CardScene.show = function() {
	SceneManager.changeTo(new CardScene(), TransitionScene.slideInL, 1.2);
}