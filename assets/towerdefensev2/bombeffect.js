var Bombeffect = clazz(Sprite, {
	texture : null,
	
	constructor : function() {
		this.callsuper();
		this.texture = new Texture2D({
			fileName : "img/bombeffect.png"
		});
		this.initWithTexture(this.texture);
		this.setTextureRect(0, 0, 55, 77);
	},
	finshBombed : function(sender) {
		
		var parent = sender.getParent();
		parent.removeChildByTag(10, true);
	},
	run : function() {
		var frameArray = new Array();
		for ( var i = 0; i <= 1; i++) {
			for ( var j = 0; j <= 9; j++) {
				var frame = new SpriteFrame({
					texture : this.texture,
					rect : new Rect({
						x : 55 * j,
						y : 77 * i,
						width : 55,
						height : 77
					})
				});
				frameArray.push(frame);
			}
		}
		var animation = new Animation({
			frames : frameArray,
			delay : 0.08
		});
		var animate1 = new Animate({
			animation : animation,
			restoreFrame : false
		});
		var finshedBombedCallback = new CallFunc({
			handler : this.finshBombed,
			data : this
		});
		var sequence = new Sequence({
			animate1 : animate1,
			callback : finshedBombedCallback
		});
		this.runAction(sequence);
	}
});