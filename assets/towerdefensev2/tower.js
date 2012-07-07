var Tower = clazz(Sprite, {
	towerTexture : null,
	target : null,
	constructor : function() {
		this.callsuper();
		this.towerTexture = new Texture2D({
			fileName : "img/tower.png"
		});
		this.initWithTexture(this.towerTexture);
		this.setTextureRect(0, 0, 60, 65);
		this.schedule(this.searchTarget, 1.2);
	},
	putProjectFrame : function() {
		var frameArray = new Array();
		for ( var i = 4; i <= 11; i++) {
			var frame = new SpriteFrame({
				texture : this.towerTexture,
				rect : new Rect({
					x : 60 * i,
					y : 65,
					width : 60,
					height : 65
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.04
		});
	},
	pullFrame : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 8; i++) {
			var frame = new SpriteFrame({
				texture : this.towerTexture,
				rect : new Rect({
					x : 60 * i,
					y : 0,
					width : 60,
					height : 65
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.04
		});
	},
	smokeFrame : function() {
		var frameArray = new Array();
		for ( var i = 9; i <= 11; i++) {
			var frame = new SpriteFrame({
				texture : this.towerTexture,
				rect : new Rect({
					x : 60 * i,
					y : 0,
					width : 60,
					height : 65
				})
			});
			frameArray.push(frame);
		}
		for ( var i = 0; i <= 3; i++) {
			var frame = new SpriteFrame({
				texture : this.towerTexture,
				rect : new Rect({
					x : 60 * i,
					y : 65,
					width : 60,
					height : 65
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.04
		});
	},
	searchTarget : function() {
		if (globalData.monsters != null) {
			var closeMonseter = null;
			var targetPos;
			var curDistance;
			var maxDistant = 9999;
			for ( var i = 0; i < globalData.monsters.length; i++) {
				targetPos = globalData.monsters[i].getPosition();
				curDistance = Point.distance(this.getPosition(), targetPos);
				if (curDistance < maxDistant) {
					closeMonseter = globalData.monsters[i];
					maxDistant = curDistance;
				}
			}
			if (maxDistant < 100) {
				this.target = closeMonseter;
				this.fire();
			}
		}
	},
	firing : function(sender) {
		if (sender.target) {
			var projectile = new Projectile();
			var selfPos = sender.getPosition();
			var startPoint = new Point({
				x : selfPos.x + 5,
				y : selfPos.y + 30
			});
			projectile.setPosition(startPoint.x, startPoint.y);
			sender.getParent().addChild(projectile, 3);
			var targetPos = sender.target.getNextWayPoint();
			projectile.run(startPoint, new Point({
				x : targetPos.x,
				y : targetPos.y
			}));
		}
	},
	fire : function() {
		var animate1 = new Animate({
			animation : this.putProjectFrame(),
			restoreFrame : false
		});
		var animate2 = new Animate({
			animation : this.pullFrame(),
			restoreFrame : false
		});
		var animate3 = new Animate({
			animation : this.smokeFrame(),
			restoreFrame : false
		});
		var fireCallback = new CallFunc({
			handler : this.firing,
			data : this
		});
		var sequence = new Sequence({
			animate1 : animate1,
			animate2 : animate2,
			callback : fireCallback,
			animate3 : animate3
		});
		this.runAction(sequence);
	}
});
