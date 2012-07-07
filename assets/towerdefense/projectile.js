include('towerdefense/bombeffect.js');

var Projectile = clazz(Sprite, {
	range1 : 85,
	range2 : 60,
	constructor : function() {
		this.callsuper();
		this.initWithFile("img/projectile.png");
	},
	finshedRun : function(sender) {
		var effect = new Bombeffect();
		var parent = sender.getParent();
		parent.addChild(effect, 4, 10);
		var selfPos = sender.getPosition();
		effect.setAnchorPoint(0.5, 0);
		effect.setPosition(selfPos.x, selfPos.y - 18);
		effect.run();
		for ( var i = 0; i < globalData.monsters.length; i++) {
			var target = globalData.monsters[i];
			var targetPos = target.getPosition();
			var distance = Point.distance(selfPos, targetPos);
			if (distance < sender.range2) {
				target.curHp = target.curHp - 40;
			} else if (distance < sender.range1) {
				target.curHp = target.curHp - 20;
			}
		}
		parent.removeChild(sender, true);
	},
	run : function(startPoint, endPoint) {
		var sx = startPoint.x;
		var sy = startPoint.y;
		var ex = endPoint.x;
		var ey = endPoint.y;
		var h = this.getContentSize().height * 0.5;
		var p1 = new Point({
			x : sx,
			y : sy
		});
		var p2 = new Point({
			x : sx + (ex - sx) * 0.5,
			y : sy + (ey - sy) * 0.5 + 100
		});
		var p3 = new Point({
			x : endPoint.x,
			y : endPoint.y
		});
		var bezier = new BezierTo({
			controlPoint1 : p1,
			controlPoint2 : p2,
			endPoint : p3,
			duration : 0.6
		});
		var rotate = new RotateBy({
			angle : 360,
			duration : 0.4
		});
		var repeate = new Repeat({
			action : rotate,
			time : 4
		});
		var spawn = new Spawn({
			bezier : bezier,
			rotate : rotate
		});
		var finshedCallback = new CallFunc({
			handler : this.finshedRun,
			data : this
		});
		var sequence = new Sequence({
			spawn : spawn,
			callback : finshedCallback
		});
		this.runAction(sequence);
	}
});