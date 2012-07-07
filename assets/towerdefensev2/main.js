require('towerdefensev2/monster.js');
require('towerdefensev2/tower.js');
require('towerdefensev2/map.js');
require('towerdefensev2/towers.js');
require('towerdefensev2/monsters.js');
require('towerdefensev2/maps.js');
require('towerdefensev2/worldScene.js');
require('towerdefensev2/cardScene.js');
require('towerdefensev2/blood.js');
require('towerdefensev2/bombeffect.js');
require('towerdefensev2/healthbar.js');
require('towerdefensev2/projectile.js');

var MainLayer = clazz(Layer, {
	constructor : function() {
		this.callsuper();
		this.initBg();
		this.initMenu();
	},
	initMenu : function() {
		var winSize = Application.getWinSize();
		var soundMenu = MenuItemImage({
			normalImage : LoadingImgs.sound,
			selectedImage : LoadingImgs.soundoff,
			handler : function(item) {
			}
		});
		var musicMenu = MenuItemImage({
			normalImage : LoadingImgs.music,
			selectedImage : LoadingImgs.musicoff,
			handler : function(item) {
			}
		});
		var twiterMenu = MenuItemImage({
			normalImage : LoadingImgs.t1,
			selectedImage : LoadingImgs.t2,
			handler : function(item) {
			}
		});
		var faceBookMenu = MenuItemImage({
			normalImage : LoadingImgs.f1,
			selectedImage : LoadingImgs.f2,
			handler : function(item) {
			}
		});
		var startMenu = MenuItemImage({
			normalImage : LoadingImgs.start1,
			selectedImage : LoadingImgs.start2,
			handler : function(item) {
				WorldScene.show();
			}
		});
		var menu1 = new Menu({
			item1 : startMenu,
		});
		var menu2 = new Menu({
			item1 : twiterMenu,
			item2 : faceBookMenu,
		});
		var menu3 = new Menu({
			item1 : soundMenu,
			item2 : musicMenu,
		});
		soundMenu.setPosition(20, winSize.height - 25);
		musicMenu.setPosition(60, winSize.height - 25);
		twiterMenu.setPosition(winSize.width - 45, winSize.height - 25);
		faceBookMenu.setPosition(winSize.width - 45, winSize.height - 90);
		menu1.setPosition(winSize.width / 2, 100);
		menu2.setPosition(0, 0);
		menu3.setPosition(0, 0);
		this.addChild(menu1, 1);
		this.addChild(menu2, 1);
		this.addChild(menu3, 1);
	},
	initBg : function() {
		var bg = new Sprite({
			fileName : LoadingImgs.bg
		});
		bg.setAnchorPoint(0, 0);
		this.addChild(bg);
	}
});
var MainScene = clazz(Scene, {
	constructor : function() {
		this.callsuper();
		this.createMenu();
		this.addChild(new MainLayer());
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

MainScene.show = function() {
	SceneManager.changeTo(new MainScene(), TransitionScene.rotoZoom, 1.2);
}