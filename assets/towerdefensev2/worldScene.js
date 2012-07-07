var WorldScene = clazz(Scene, {
	map : null,
	constructor : function() {
		this.callsuper();
		this.initBg();
		this.initMenu();
		this.initFlag();
	},
	initMenu : function() {
		var winSize = Application.getWinSize();
		var mainMenuItem = MenuItemImage({
			normalImage : LoadingImgs.mainMenu,
			selectedImage : LoadingImgs.mainMenuSelect,
			handler : function(item) {
				MainScene.show();
			}
		});
		var upgradeMenuItem = MenuItemImage({
			normalImage : LoadingImgs.upgradeMenu,
			selectedImage : LoadingImgs.upgradeMenuSelect,
			handler : function(item) {
			}
		});
		var baikeMenuItem = MenuItemImage({
			normalImage : LoadingImgs.baikeMenu,
			selectedImage : LoadingImgs.baikeMenuSelect,
			handler : function(item) {
			}
		});
		var chenjiuMenuItem = MenuItemImage({
			normalImage : LoadingImgs.chenjiuMenu,
			selectedImage : LoadingImgs.chenjiuMenuSelect,
			handler : function(item) {
			}
		});
		var mainMenu = new Menu({
			item1 : mainMenuItem,
			item2 : upgradeMenuItem,
			item3 : baikeMenuItem,
			item4 : chenjiuMenuItem
		});
		mainMenuItem.setPosition(50, 90);
		upgradeMenuItem.setPosition(winSize.width / 2 + 40, 90);
		baikeMenuItem.setPosition(winSize.width / 2 + 95, 90);
		chenjiuMenuItem.setPosition(winSize.width / 2 + 150, 90);
		var childs = mainMenu.getChildren();
		for ( var i = 0; i < childs.length; i++) {
			var moveBy = new MoveBy({
				point : new Point({
					x : 0,
					y : -60
				}),
				duration : 1.5
			});
			var speed = new Speed({
				action : moveBy,
				rate : 1.2
			});
			childs[i].runAction(speed);
		}
		mainMenu.setPosition(0, 0);
		this.addChild(mainMenu, 1);
	},
	initBg : function() {
		this.map = new TMXTiledMap({
			mapFile : 'img/bgmap.tmx'
		});
		this.addChild(this.map, 0);
	},
	initFlag : function() {
		var group = this.map.objectGroupNamed("flag");
		var objects = group.getObjects();
		if (objects) {
			var x = 0;
			var y = 0;
			for ( var i = 0; i < objects.length; i++) {
				x = objects[i].getIntValue("x");
				y = objects[i].getIntValue("y");
				var falgMenuItem = new MenuItemImage({
					normalImage : LoadingImgs.flag1,
					selectedImage : LoadingImgs.flag1,
					handler : this.flagHanldler
				});
				falgMenuItem.setTag(i + 1);
				falgMenuItem.setAnchorPoint(0.5, 0);
				falgMenuItem.setPosition(x, y + 40);
				var falgMenu = new Menu({
					item1 : falgMenuItem,
				});
				falgMenu.setPosition(0, 0);
				this.addChild(falgMenu, 1);
				var moveBy = new MoveBy({
					point : new Point({
						x : 0,
						y : -40
					}),
					duration : 1.5
				});
				var speed = new Speed({
					action : moveBy,
					rate : 1.2
				});
				falgMenuItem.runAction(speed);
			}
		}
	},
	flagHanldler : function(item) {
		var card = item.getTag();
		switch (card) {
		case 1:
			CardScene.show();
			break;
		default:
			break;
		}
	}
});

WorldScene.show = function() {
	SceneManager.changeTo(new WorldScene(), TransitionScene.slideInL, 1.2);
}