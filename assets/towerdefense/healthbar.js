var HealthBar = clazz(Sprite, {
	constructor : function() {
		this.callsuper();
		var texture = new Texture2D({
			fileName : "img/hp_1.png"
		});
		this.initWithTexture(texture);
		this.setTextureRect(9 * 25, 0, 25, 4);
	},
	update : function(percent) {
		var index = (percent * 0.1) - 1;
		if (index > 0) {
			this.setTextureRect(index * 25, 0, 25, 4);
		}
	}
});