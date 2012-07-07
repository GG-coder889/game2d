var BombLayer = clazz(Layer, {
	bullets : null,
	hero : null,
	eplosionSprite : null,
	tempObject : null,
	count : 0,
	constructor : function() {
		this.callsuper();
		this.createSprite();
		this.createExplosionSprite();
		var mainScene = new MenuItemFont({
			title : "mainScene",
			handler : showsceneOne
		});
		mainScene.setPosition(screenWidth - 20, 20);
		var mainMenu = new Menu({
			item : mainScene
		});
		mainMenu.setPosition(0, 0);
		this.addChild(mainMenu, 1);
		this.bullets = new Array();
		this.schedule(this.checkCollision, 0);
		this.schedule(this.createBullet, 0);
		this.schedule(this.checkHero, 0);
	},
	createExplosionSprite : function() {
		var texture = new Texture2D({
			fileName : "img/explosion.png"
		});
		this.eplosionSprite = Sprite.spriteWithTexture({
			texture : texture,
			rect : new Rect({
				x : 0,
				y : 0,
				width : 32,
				height : 32
			})
		});
		this.addChild(this.eplosionSprite, 1);
		this.eplosionSprite.setIsVisible(false);
	},
	hitCount : 0,
	onEplosionDone : function(obj) {
		obj.eplosionSprite.setIsVisible(false);
		obj.hitCount++;
		if (obj.hitCount == 3) {
			obj.removeChild(obj.hero, true);
			obj.createSprite();
			obj.hitCount = 0;
		}
	},
	showEplosion : function() {
		var texture = new Texture2D({
			fileName : "img/explosion.png"
		});
		var frameArray = new Array();
		for ( var i = 0; i < 4; i++) {
			var frame = new SpriteFrame({
				texture : texture,
				rect : new Rect({
					x : 32 * i,
					y : 0,
					width : 32,
					height : 32
				})
			});
			frameArray.push(frame);
		}
		var animation = new Animation({
			frames : frameArray,
			delay : 0.2
		});
		var animate = new Animate({
			animation : animation,
			restoreFrame : true
		});
		var eplosionOver = new CallFunc({
			handler : this.onEplosionDone,
			data : this
		});
		var sequence = new Sequence({
			animate : animate,
			callback : eplosionOver
		});
		this.eplosionSprite.setIsVisible(true)
		var p = this.hero.getPosition();
		this.eplosionSprite.setPosition(p.x, p.y);
		this.eplosionSprite.runAction(sequence);
	},
	checkHero : function(dt) {
		if (this.hero) {
			var heroPosition = this.hero.getPosition();
			var winSize = Application.getWinSize();
			var screen = new Rect({
				x : 0,
				y : 0,
				width : winSize.width,
				height : winSize.height
			});
			var isContained = Rect.rectContainsPoint(screen, heroPosition);
			if (!isContained) {
				this.removeChild(this.hero, true);
				this.createSprite();
			}
		}
	},
	checkBullet : function(dt) {
		// var winSize = Application.getWinSize();
		var screen = new Rect({
			x : 0,
			y : 0,
			width : 480,
			height : 320
		});
		for ( var i = 0; i < obj.bullets.length; i++) {
			var bullet = this.bullets[i];
			var bulletPosition = bullet.getPosition();
			var isContained = Rect.rectContainsPoint(screen, bulletPosition);
			if (!isContained) {
				this.bullets.splice(i, 1);
				this.removeChild(bullet, true);
			}
		}
	},
	checkCollision : function(dt) {
		if (this.hero) {
			var heroBox = this.hero.boundingBox();
			var winSize = Application.getWinSize();
			var screen = new Rect({
				x : 0,
				y : 0,
				width : winSize.width,
				height : winSize.height
			});
			for ( var i = 0; i < this.bullets.length; i++) {
				var bullet = this.bullets[i];
				var bulletPosition = bullet.getPosition();
				var bulletBox = bullet.boundingBox();
				var isContained = Rect
						.rectContainsPoint(screen, bulletPosition);
				var isIntersects = Rect.rectIntersectsRect(heroBox, bulletBox);
				if (!isContained || isIntersects) {
					this.bullets.splice(i, 1);
					this.removeChild(bullet, true);
				}
			}
		}
	},
	bulletRun : function(bullet) {
		var x = 480 - 4;
		var y = abs(random() % 320);

		var speedX = abs(random() % 3 + 1) * -1;
		var speedY = random() % 3;
		var p = new Point({
			x : speedX,
			y : speedY
		});
		var action = new MoveBy({
			duration : 0.000001,
			point : p
		});
		bullet.setPosition(x, y);
		bullet.runAction(new RepeatForever({
			action : action
		}));
	},
	createBullet : function(dt) {

		var texture = new Texture2D({
			fileName : "img/bullet.png"
		});
		var bulletSprite = Sprite.spriteWithTexture({
			texture : texture
		});
		this.bullets.push(bulletSprite);
		this.addChild(bulletSprite);
		this.count++;
		this.bulletRun(bulletSprite);

		this.checkCollision(dt);

	},
	heroRun : function() {
		var winSize = Application.getWinSize();
		var animate = new Animate({
			animation : this.createHeroAnimation(),
			restoreFrame : false
		});

		var x = this.hero.boundingBox().size.width;
		var y = abs(random() % winSize.height);
		var speedX = abs(random() % 3 + 1);
		var speedY = random() % 3;
		var move = new MoveBy({
			duration : 0.001,
			point : new Point({
				x : speedX,
				y : speedY
			})
		});
		var spawn = new Spawn({
			animate : animate,
			move : move
		});
		var action = new RepeatForever({
			action : spawn
		});
		this.hero.setPosition(x, y);
		this.hero.runAction(action);
	},
	createHeroAnimation : function() {
		var heroTexture = new Texture2D({
			fileName : "img/hero.png"
		});

		var frameArray = new Array();
		for ( var i = 0; i < 4; i++) {
			var frame = new SpriteFrame({
				texture : heroTexture,
				rect : new Rect({
					x : 32 * i,
					y : 32 * 2,
					width : 32,
					height : 32
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.07
		});

	},
	createSprite : function() {
		var spriteFrame = this.createHeroAnimation().getSpriteFrame(0);
		this.hero = Sprite.spriteWithSpriteFrame({
			frame : spriteFrame
		});
		this.addChild(this.hero);
		this.heroRun();
	}

});

var BombScene = clazz(Scene, {
	constructor : function() {
		this.callsuper();
		this.addChild(new BombLayer());
	}
});

function runBombScene1() {
	SceneManager.changeTo(new BombScene(), TransitionScene.flipX, 1.2);
}