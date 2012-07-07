var box2dScene;
var box2dLayer;
var world;
var PTM_RATIO = 32;
var spriteMgr = 1;
var debugDraw;
var mgr;
function initWorld() {

	world = new b2World(0.0, -10.0);
	world.setAllowSleeping(true);
	world.setContinuousPhysics(true);
	var groundBodyDef = new b2BodyDef();

	var halfOfScreenWidth = screenWidth / PTM_RATIO;
	var halfOfScreenHeight = screenHegiht / PTM_RATIO;
	groundBodyDef.setPosition(0, 0);
	var groundBody = world.createb2Body(groundBodyDef);
	var groundBox = new b2PolygonShape();

	// bottom
	groundBox.setAsBox(halfOfScreenWidth, 0, 0, 0, 0);
	groundBody.createFixture(groundBox, 0);

	// top
	groundBox.setAsBox(halfOfScreenWidth, 0, 0, halfOfScreenHeight, 0);
	groundBody.createFixture(groundBox, 0);

	// left
	groundBox.setAsBox(0, halfOfScreenHeight, 0, 0, 0);
	groundBody.createFixture(groundBox, 0);

	// right
	groundBox.setAsBox(0, halfOfScreenWidth, halfOfScreenWidth,
			halfOfScreenHeight, 0);

	groundBody.createFixture(groundBox, 0);
}

function initItems() {
	mgr = new SpriteBatchNode({
		fileName : "img/blocks.png",
		capacity : 150
	});
	var tabLabel = new LabelTTF({
		label : "Tap screen",
		fontName : "Marker Felt",
		fontSize : 32
	});
	tabLabel.setPosition(screenWidth / 2, screenHegiht - 50);
	Debug.log("initItems", "---initItems----");
	var mainScene = new MenuItemFont({
		title : "mainScene",
		handler : showsceneOne
	});
	mainScene.setPosition(screenWidth - 20, 20);
	var mainMenu = new Menu({
		item : mainScene
	});
	mainMenu.setPosition(0, 0);
	tabLabel.setColor(0, 0, 255);
	box2dLayer.addChild(mgr, 0, spriteMgr);
	box2dLayer.addChild(tabLabel, 0);
	box2dLayer.addChild(mainMenu, 0);
	Debug.log("initItems", "11");
	addNewSpriteWithCoords(screenWidth / 2, screenHegiht / 2);
}

function addNewSpriteWithCoords(x, y) {
	var idx = random01() > 0.5 ? 0 : 1;
	var idy = random01() > 0.5 ? 0 : 1;
	var spriteTexture = mgr.getTexture();
	var sprite = Sprite.spriteWithTexture({
		texture : spriteTexture,
		rect : new Rect({
			x : 32 * idx,
			y : 32 * idy,
			width : 32,
			height : 32
		})
	});
	mgr.addChild(sprite);
	sprite.setPosition(x, y);
	var bodyDef = new b2BodyDef();
	bodyDef.type = b2Body.dynamicBody;
	bodyDef.setPosition(x / PTM_RATIO, y / PTM_RATIO);
	bodyDef.setUserData(sprite);
	var body = world.createb2Body(bodyDef);
	var dynamicBox = new b2PolygonShape();
	dynamicBox.setAsBox(0.5, 0.5);
	var fixtureDef = new b2FixtureDef();
	fixtureDef.setShape(dynamicBox);
	fixtureDef.setDensity(1.0);
	fixtureDef.setFriction(0.3);
	body.createFixture(fixtureDef);
}
function update(dt) {

	var velocityIterations = 8;
	var positionIterations = 1;

	world.step(dt, velocityIterations, positionIterations);

	var bodyCount = world.getBodyCount();
	var b = world.getBodyList();
	var sprite;
	while (b != null) {
		var userData = b.getUserData();
		if (userData != null) {
			sprite = Sprite.cast(userData);
			var pos = b.getPosition();
			var x = pos.x * PTM_RATIO;
			var y = pos.y * PTM_RATIO;
			var rotation = radiansToDegrees(b.getAngle()) * -1;
			sprite.setPosition(x, y);
			sprite.setRotation(rotation);
		}
		b = b.getNext();
	}
}

function onTouchedCallback(x, y) {
	addNewSpriteWithCoords(x, y);
}

function showBox2dScene() {

	box2dScene = new Scene();
	box2dLayer = new Layer();

	box2dLayer.setIsTouchEnabled(true);
	box2dLayer.setIsAccelerometerEnabled(true);
	schedule(update, 0.001);
	box2dLayer.onTouchesEnded = onTouchedCallback;

	initWorld();
	initItems();

	box2dScene.addChild(box2dLayer);

	SceneManager.changeTo(box2dScene);
}