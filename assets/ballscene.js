var ballScene;
var ballLayer;
var ballWorld;
var PTM_RATIO = 32;
var balldebugDraw;

function initBallWorld() {
	balldebugDraw = new DebugDraw({
		ratio : PTM_RATIO
	});
	ballWorld = new b2World(0.0, -10.0);
	ballWorld.setDebugDraw(balldebugDraw);
	balldebugDraw.setFlags();
	ballWorld.setAllowSleeping(true);
	ballWorld.setContinuousPhysics(true);
	var groundBodyDef = new b2BodyDef();

	var halfOfScreenWidth = screenWidth / PTM_RATIO;
	var halfOfScreenHeight = screenHegiht / PTM_RATIO;
	groundBodyDef.setPosition(0, 0);
	var groundBody = ballWorld.createBody(groundBodyDef);
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

function initBallItem() {
	var sprite = new Sprite({
		fileName : "img/Icon.png"
	});
	sprite.setPosition(screenWidth / 2, screenWidth / 2);
	ballLayer.addChild(sprite, 0);
	var ballBodyDef = new b2BodyDef();
	ballBodyDef.type = b2Body.dynamicBody;
	ballBodyDef.setPosition(screenWidth / 2 / PTM_RATIO, screenHegiht / 2
			/ PTM_RATIO);
	ballBodyDef.setUserData(sprite);
	var body = ballWorld.createBody(ballBodyDef);
	var circle = new b2CircleShape();
	circle.setRadius(26.0 / PTM_RATIO);
	var fixtureDef = new b2FixtureDef();
	fixtureDef.setShape(circle);
	fixtureDef.setDensity(1.0);
	fixtureDef.setFriction(0.2);
	fixtureDef.setRestitution(0.3);
	body.createFixture(fixtureDef);
}

function updateCallback(dt) {

	var velocityIterations = 10;
	var positionIterations = 10;
	ballWorld.step(dt, velocityIterations, positionIterations);
	var b = ballWorld.getBodyList();
	while (b != null) {
		var userData = b.getUserData();
		if (userData != null) {
			var sprite = userData;
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

function onDrawCallback() {
	ballWorld.drawDebugData();
}

function showBallScene() {

	ballScene = new Scene();
	ballLayer = new DebugLayer();

	ballLayer.setIsTouchEnabled(true);
	ballLayer.setIsAccelerometerEnabled(true);
	schedule(updateCallback, 0.001);

	initBallWorld();
	initBallItem();

	var mainScene = new MenuItemFont({
		title : "mainScene",
		handler : showsceneOne
	});
	mainScene.setPosition(screenWidth - 20, 20);
	var mainMenu = new Menu({
		item : mainScene
	});
	mainMenu.setPosition(0, 0);
	ballLayer.addChild(mainMenu);
	ballLayer.onDraw = onDrawCallback;
	ballScene.addChild(ballLayer);

	SceneManager.changeTo(ballScene);
}