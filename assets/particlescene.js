function showParticleScene() {
	var s = new Scene();
	var l = new Layer();
	var mainScene = new MenuItemFont({
		title : "mainScene",
		handler : showsceneOne
	});
	mainScene.setPosition(screenWidth - 20, 20);
	var mainMenu = new Menu({
		item : mainScene
	});
	mainMenu.setPosition(0, 0);
	l.addChild(mainScene);
	s.addChild(l);
	SceneManager.changeTo(s);
}