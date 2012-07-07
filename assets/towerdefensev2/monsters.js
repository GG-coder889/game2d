var Monsters = [ {
	xtype : "Monster1",
	overrides : {
		speed : 55,
		constructor : function() {
			this.callsuper();
			this.texture = new Texture2D({
				fileName : "img/m_14.png"
			});
			this.initWithTexture(this.texture);
			this.setTextureRect(0, 0, 45, 40);
		}
	}
}, ];
