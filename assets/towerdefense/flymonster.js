var FlyMonster = clazz(Sprite, {
	hasRun : false,
	moveDuration : 0,
	curWaypoint : 0,
	monsterTexture : null,
	wayPoint : null,
	constructor : function() {
		this.callsuper();
		var spriteFrame = this.forwardMoveFrame().getSpriteFrame(0);
		this.initWithSpriteFrame(spriteFrame);
	},
	getMoveAnimate : function(p1, p2) {
		if (p1.x > p2.x) {
			return this.rightMoveFrame();
		} else if (p1.x < p2.x) {
			return this.leftMoveFrame();
		}
		return this.forwardMoveFrame();
	},
	followPath : function(sender) {
		++sender.curWaypoint;
		if (sender.curWaypoint < sender.wayPoint.length) {
			var currentPos = sender.getPosition();
			var nextPoint = sender.wayPoint[sender.curWaypoint];
			var distance = Point.distance(nextPoint, currentPos);
			var duration = distance / 80;
			var move = new MoveTo({
				duration : duration,
				point : nextPoint
			});
			var moveCallback = new CallFunc({
				handler : sender.followPath,
				data : sender
			});
			var animate = new Animate({
				animation : sender.getMoveAnimate(nextPoint, currentPos),
				restoreFrame : false
			});
			var spawn = new Spawn({
				animate : animate,
				move : move
			});
			var sequence = new Sequence({
				spawn : spawn,
				callback : moveCallback
			});
			sender.stopAllActions();
			sender.runAction(sequence);
		} else {
			sender.hasRun = true;
		}
	},
	move : function() {
		this.setPosition(this.wayPoint[0].x, this.wayPoint[0].y + 50);
		this.followPath(this);
	},
	leftMoveFrame : function() {
		var frameArray = new Array();
		for ( var i = 14; i <= 16; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 49 * i,
					y : 0,
					width : 49,
					height : 49
				})
			});
			frameArray.push(frame);
		}
		for ( var i = 0; i <= 10; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 49 * i,
					y : 87,
					width : 49,
					height : 49
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.05
		});
	},
	rightMoveFrame : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 13; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 49 * i,
					y : 0,
					width : 49,
					height : 49
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.05
		});
	},
	forwardMoveFrame : function() {
		this.monsterTexture = new Texture2D({
			fileName : "img/m_19.png"
		});
		var frameArray = new Array();
		for ( var i = 8; i <= 16; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 49 * i,
					y : 174,
					width : 49,
					height : 49
				})
			});
			frameArray.push(frame);
		}
		for ( var i = 0; i <= 4; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 49 * i,
					y : 261,
					width : 49,
					height : 49
				})
			});
		}
		frameArray.push(frame);
		return new Animation({
			frames : frameArray,
			delay : 0.05
		});
	}
});