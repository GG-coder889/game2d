var Tower = XComponent.extend("Tower", Sprite, {
	damage : 0,
	range : 0,
	speed : 0,
	type : null,
	ability : 0,
	ballistic : 'line',
	projectileTexture : null,
	projectileEffect : null,
	texture : null,
	constructor : function() {
		this.callsuper();
		this.texture = new Texture2D({
			fileName : this.texture
		});
		this.initWithTexture(this.texture);
		this.setTextureRect.apply(this, this.textureRect);
	},
	caculate : function(target) {

	}
});
