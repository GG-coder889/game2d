/*var Tower = Component.extend('tower', Sprite, {
	constructor:		function() {
		this.callsuper();
		this.texture = new Textrue2D({fileName: this.texture});
		this.initWithTexture(this.texture);
		this.setTextureRect.apply(this, this.textureRect);
	},
	shoot:				function() {
		pos = this.shootwhere();
		this.shootanimate();
	},
	shootanimate:		function() {
		this.beforeshootanimate();
		this.createbullet();// xxxxxx
		this.aftershootanimate();
	},
	this.beforeshootanmiate:	function() {
		this.animate.apply(beforeshootanimation);
	}
	
});*/

var Towers = {
	tower1 : {
		texture : 'img/tower.png',
		textureRect : [ 0, 0, 60, 65 ],
	}
}
