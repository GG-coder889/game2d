require("base/game2d.js");
require("base/game2d-simple.js");
require('gamescene.js');
require('box2dscene.js');
require('ballscene.js');
require('particlescene.js');
require('tweejump.js');
require('anotherbombscene.js');
// require('towerdefense/main.js');
require('towerdefensev2/loadingScene.js');
Application.setDisplayFPS(true);
var winSize = Application.getWinSize();
var screenWidth = winSize.width;
var screenHegiht = winSize.height;
var iconWidth1 = 57;
var layerColor;
var beganTouchX;
var beganTouchY;
var curX;
var curY;
var menuCount = 7;
var menuSpace = 40;
var menuArray = new Array("towerdefense", "gameScene", "box2dScene",
		"ballScene", "ParticleScene", "tweejumpScene", "bombscene");

function endGame(item) {
	Application.exit();
}

function showsceneOne() {
	SceneManager.changeTo(new StartScene(), TransitionScene.rotoZoom, 1.2);
}

var MenuLayer = clazz(Layer,
		{
			constructor : function() {
				this.callsuper();
				var sprite = new Sprite({
					fileName : "img/Icon.png"
				});
				var moveBy = new MoveBy({
					point : new Point({
						x : 0,
						y : 40
					}),
					duration : 4
				});
				var easeElasticOut = new EaseElasticOut({
					action : moveBy,
					period : 0.35
				});
				sprite.setPosition(screenWidth / 2, screenHegiht / 2);
				sprite.runAction(moveBy);
				var close = new MenuItemImage({
					normalImage : "img/CloseNormal.png",
					selectedImage : "img/CloseNormal.png",
					handler : function(item) {
						Application.exit();
					}
				});
				var closeMenu = new Menu({
					item1 : close,
				});
				closeMenu.setPosition(screenWidth - 30, screenHegiht - 30);

				this.createMainMenu();

				this.setIsTouchEnabled(true);
				this.onTouchMoved(this.touchMoved);
				this.onTouchBegan(this.touchBegan);
				this.addChild(this.mainMenus, 1);
				this.addChild(closeMenu, 2);
				this.addChild(sprite, 0);
			},
			mainMenus : null,
			createMainMenu : function() {
				this.mainMenus = new Menu();
				var x = screenWidth / 2;
				var y;
				for ( var i = 0; i < menuCount; i++) {
					var menuItem = new MenuItemFont({
						title : menuArray[i],
						handler : function(item) {
							if (item != null) {
								var zOrder = item.getZOrder();
								var option = zOrder - 10000;
								if (option == 0) {
									LoadingScene.show();
								} else if (option == 1) {
									showGameScene();
								} else if (option == 2) {
									showBox2dScene();
								} else if (option == 3) {
									showBallScene();
								} else if (option == 4) {
									showParticleScene();
								} else if (option == 5) {
									showtweejumpScene();
								} else if (option == 6) {
									runBombScene1();
								}
							}
						}
					});
					this.mainMenus.addChild(menuItem, i + 10000);
					y = screenHegiht - (i + 1) * menuSpace;
					menuItem.setPosition(x, y);
				}
				this.mainMenus.setContentSize(screenWidth, (menuCount + 1)
						* menuSpace);
				this.mainMenus.setPosition(0, 0);
			},
			touchBegan : function(touch) {
				var p = touch.location();
				this.beganTouchX = p.x;
				this.beganTouchY = p.y;
			},
			touchMoved : function(touch) {
				var p = touch.location();
				var movedY = p.y - this.beganTouchY;
				var menuPosition = this.mainMenus.getPosition();
				var currentMenuX = menuPosition.x;
				var currentMenuY = menuPosition.y;
				var nextPosY = currentMenuY + movedY;
				if (nextPosY < 0.0) {
					this.mainMenus.setPosition(0, 0);
					return;
				}
				var maxPosY = (menuCount + 1) * menuSpace - screenHegiht;
				if (nextPosY > maxPosY) {
					this.mainMenus.setPosition(0, maxPosY);
					return;
				}
				this.mainMenus.setPosition(currentMenuX, nextPosY);
				this.beganTouchX = p.x;
				this.beganTouchY = p.y;
			}
		});

var StartScene = clazz(Scene, {
	constructor : function() {
		this.callsuper();
		this.addChild(new MenuLayer());
	}
});
Application.start(new StartScene());
