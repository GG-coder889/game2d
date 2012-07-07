require("towerdefensev2/loadingImgs.js");
require("towerdefensev2/main.js");
var LoadingScene = clazz(Scene, {
	loadIndex : 0,
	loadingTimerId : 0,
	percentage : null,
	imgsArray : null,
	constructor : function() {
		this.callsuper();
		var winSize = Application.getWinSize();
		var loading = new Sprite({
			fileName : "img/loading.png"
		});
		this.title = new LabelTTF({
			label : "载入中 ......",
			fontName : "Thonburi",
			fontSize : 18
		});
		loading.setPosition(winSize.width / 2, winSize.height / 2);
		this.title.setPosition(winSize.width / 2, 20);
		this.addChild(loading);
		this.addChild(this.title, 1);
		this.imgsArray = LoadingImgs.toArray();
		this.loadingTimerId = this.schedule(this.onLoadingTimer, 0.1);
	},
	onLoadingTimer : function() {
		if (this.loadIndex < this.imgsArray.length) {
			TextureCache.addImage(this.imgsArray[this.loadIndex]);
			this.loadIndex++;
			var percentage = (this.loadIndex / this.imgsArray.length) * 100;
			if (percentage < 100) {
				percentage = Math.round(percentage + 0.5);
			}
			this.title.setString('已加载  ' + percentage + '%');
		} else {
			this.unschedule(this.loadingTimerId);
			MainScene.show();
		}
	}
});

LoadingScene.show = function() {
	SceneManager
			.changeTo(new LoadingScene(), TransitionScene.flipAngular, 0.12);
}