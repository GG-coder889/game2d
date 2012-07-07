var Monster = clazz(Sprite, {
	hp : 0,
	armor : null,
	armorType : null,
	speed : 0,
	ability : 0,
	texture : null,
	wayPoint : null,
	curWaypoint : 0,
	hasRun : false,
	constructor : function() {
		this.callsuper();
		this.hasRun = false;
	},
	moveRight : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 7; i++) {
			var frame = new SpriteFrame({
				texture : this.texture,
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
	moveLeft : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 6; i++) {
			var frame = new SpriteFrame({
				texture : this.texture,
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
				texture : this.texture,
				rect : new Rect({
					x : 45 * i,
					y : 0,
					width : 45,
					height : 40
				})
			});
			frameArray.push(frame);
		}
		return Animation({
			frames : frameArray,
			delay : 0.05
		});
	},
	move : function() {
		this.setPosition(this.wayPoint[0].x, this.wayPoint[0].y);
		this.followPath(this);
	},
	getMoveDirection : function(p1, p2) {
		if (p1.x > p2.x) {
			return this.moveRight();
		} else if (p1.x < p2.x) {
			return this.moveLeft();
		}
		return this.moveForward();
	},
	followPath : function(sender) {
		++sender.curWaypoint;
		if (sender.curWaypoint < sender.wayPoint.length) {
			var currentPos = sender.getPosition();
			var nextPoint = sender.wayPoint[sender.curWaypoint];
			var distance = Point.distance(nextPoint, currentPos);
			var duration = distance / sender.speed;
			var move = new MoveTo({
				duration : duration,
				point : nextPoint
			});
			var moveCallback = new CallFunc({
				handler : sender.followPath,
				data : sender
			});
			var animate = new Animate({
				animation : sender.getMoveDirection(nextPoint, currentPos),
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
	moveForward : function() {
		var frameArray = new Array();
		for ( var i = 4; i <= 11; i++) {
			var frame;
			if (i == 11) {
				frame = new SpriteFrame({
					texture : this.texture,
					rect : new Rect({
						x : 0,
						y : 120,
						width : 45,
						height : 40
					})
				});
			} else {
				frame = new SpriteFrame({
					texture : this.texture,
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