include('towerdefense/blood.js');

var Monster = clazz(Sprite, {
	hasRun : false,
	moveDuration : 0,
	curWaypoint : 0,
	monsterTexture : null,
	healthBar : null,
	healthScheduleId : 0,
	score : 10,
	curHp : 100,
	constructor : function() {
		this.callsuper();
		var spriteFrame = this.forwardMoveFrame().getSpriteFrame(0);
		this.initWithSpriteFrame(spriteFrame);
		this.healthScheduleId = this.schedule(this.updateHealthBar, 0.3);
	},
	updateHealthBar : function() {
		if (this.healthBar) {
			var selfPos = this.getPosition();
			var selfSize = this.getContentSize();
			this.healthBar.update(this.curHp);
			this.healthBar.setPosition(selfPos.x, selfPos.y + selfSize.height
					/ 4);
		}
	},
	getMoveAnimate : function(p1, p2) {
		if (p1.x > p2.x) {
			return this.rightMoveFrame();
		} else if (p1.x < p2.x) {
			return this.leftMoveFrame();
		}
		return this.forwardMoveFrame();
	},
	getNextWayPoint : function() {
		if (this.curWaypoint < globalData.wayPoint.length) {
			var nextPoint = this.curWaypoint + 1;
			if (nextPoint < globalData.wayPoint.length) {
				return globalData.wayPoint[nextPoint];
			}
		}
		return this.getPosition();
	},
	followPath : function(sender) {
		++sender.curWaypoint;
		if (sender.curWaypoint < globalData.wayPoint.length) {
			var currentPos = sender.getPosition();
			var nextPoint = globalData.wayPoint[sender.curWaypoint];
			var distance = Point.distance(nextPoint, currentPos);
			var duration = distance / 55;
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
		this.setPosition(globalData.wayPoint[0].x, globalData.wayPoint[0].y);
		this.followPath(this);
	},
	rightMoveFrame : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 7; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 45 * i,
					y : 0,
					width : 45,
					height : 40
				})
			});
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.05
		});
	},
	leftMoveFrame : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 6; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 45 * i,
					y : 40,
					width : 45,
					height : 40
				})
			});
			frameArray.push(frame);
		}
		for ( var i = 11; i <= 14; i++) {
			var frame = new SpriteFrame({
				texture : this.monsterTexture,
				rect : new Rect({
					x : 45 * i,
					y : 0,
					width : 45,
					height : 40
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
			fileName : "img/m_14.png"
		});
		var frameArray = new Array();
		for ( var i = 4; i <= 11; i++) {
			var frame;
			if (i == 11) {
				frame = new SpriteFrame({
					texture : this.monsterTexture,
					rect : new Rect({
						x : 0,
						y : 120,
						width : 45,
						height : 40
					})
				});
			} else {
				frame = new SpriteFrame({
					texture : this.monsterTexture,
					rect : new Rect({
						x : 45 * i,
						y : 80,
						width : 45,
						height : 40
					})
				});
			}
			frameArray.push(frame);
		}
		return new Animation({
			frames : frameArray,
			delay : 0.05
		});
	}
});