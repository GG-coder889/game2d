var Blood = clazz(Sprite, {
	constructor : function() {
		this.callsuper();
		this.initWithFile("img/dead_blood.png");
	},
	finshShow : function(sender) {
		var p = sender.getParent();
		p.removeChild(sender, true);
	},
	show : function(x, y) {
		var fadeOut = new FadeOut({
			duration : 3
		});
		var finshedShow = new CallFunc({
			handler : this.finshShow,
			data : this
		});
		var sequence = new Sequence({
			fadeOut : fadeOut,
			callback : finshedShow
		});
		this.setPosition(x, y);
		this.runAction(sequence);
	}
});