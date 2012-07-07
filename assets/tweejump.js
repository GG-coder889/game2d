var background;
var currentCloudY;
var currentCloudTag;
var kNumClouds = 12;
var kCloudsStartTag = 100;
var kPlatformsStartTag = 200;
var kBonusStartTag = 300;
var currentPlatformY;
var currentPlatformTag;
var currentMaxPlatformStep;
var currentBonusPlatformIndex;
var currentBonusType;
var platformCount;
var kPlatformsStartTag = 200;
var kNumPlatforms = 10;
var kStartingCurrentPlatformY = 30;
var kMinPlatformStep = 50;
var kMaxPlatformStep = 300;
var kPlatformTopPadding = 10;
var kMinBonusStep = 20;
var kMaxBonusStep = 40;
var kBird = 1;
var kScoreLabel = 2;
var cloundLayer;
var birdLayer;
var bonusImg = new Array("5.png", "10.png", "50.png", "100.png");
var kBonus5 = 0;
var kBonus10 = 1;
var kBonus50 = 2;
var kBonus100 = 3;
var kNumBonuses = 4;
function initClouds() {

	currentCloudTag = kCloudsStartTag;

	while (currentCloudTag < kCloudsStartTag + kNumClouds) {
		initCloud();
		currentCloudTag++;
	}

	resetClouds();
}
function initCloud() {
	var cloud;
	switch (random() % 3) {
	case 0:
		cloud = Sprite.spriteWithSpriteFrame({
			frame : SpriteFrameCache.spriteFrameByName("cloud1.png")
		});
		break;
	case 1:
		cloud = Sprite.spriteWithSpriteFrame({
			frame : SpriteFrameCache.spriteFrameByName("cloud2.png")
		});
		break;
	case 2:
		cloud = Sprite.spriteWithSpriteFrame({
			frame : SpriteFrameCache.spriteFrameByName("cloud3.png")
		});
		break;
	}
	cloundLayer.addChild(cloud, 3, currentCloudTag);
	cloud.setOpacity(128);
}
function resetClouds() {
	currentCloudTag = kCloudsStartTag;

	while (currentCloudTag < kCloudsStartTag + kNumClouds) {
		var cloud = cloundLayer.getChildByTag(currentCloudTag);
		resetCloud(cloud);
		var cloudPos = cloud.getPosition();
		var posX = cloudPos.x;
		var posY = cloudPos.y;
		posY -= screenHegiht;
		cloud.setPosition(posX, posY);
		currentCloudTag++;
	}
}
function resetCloud(cloud) {

	var distance = random() % 20 + 5;
	var scale = 5.0 / distance;
	cloud.setScaleX(scale);
	cloud.setScaleY(scale);
	if (random() % 2 == 1)
		cloud.setScaleX(-cloud.getScaleX());
	var sizeW = cloud.getContentSize().width;
	var scaled_width = sizeW * scale;
	var x = random() % (screenWidth + scaled_width) - scaled_width / 2;
	var y = random() % (screenHegiht - scaled_width) + scaled_width / 2
			+ screenHegiht;

	cloud.setPosition(x, y);
}

function step(dt) {

	for ( var t = kCloudsStartTag; t < kCloudsStartTag + kNumClouds; t++) {
		var cloud = cloundLayer.getChildByTag(t);
		if (cloud != null) {
			var cloudPos = cloud.getPosition();
			var posX = cloudPos.x;
			var posY = cloudPos.y;
			var sizeW = cloud.getContentSize().width;
			posX += 0.1 * cloud.getScaleY();
			if (posX > screenWidth + screenWidth / 2) {
				posX = -sizeW / 2;
			}
			cloud.setPosition(posX, posY);
		}
	}
}

function initCloundLayer() {
	cloundLayer = new Layer();
	var mainScene = new MenuItemFont({
		title : "mainScene",
		handler : showsceneOne
	});
	mainScene.setPosition(screenWidth - 20, 20);
	var mainMenu = new Menu({
		itme : mainScene
	});
	mainMenu.setPosition(0, 0);
	cloundLayer.addChild(mainMenu, 1);
	SpriteFrameCache.addSpriteFramesWithFile("img/spritesheet.plist");
	background = Sprite.spriteWithSpriteFrame({
		frame : SpriteFrameCache.spriteFrameByName("background.png")
	});
	background.setPosition(screenWidth / 2, screenHegiht / 2); // center it
	initClouds();
	schedule(step, 0.001);
	cloundLayer.addChild(background);
}

function initPlatforms() {

	currentPlatformTag = kPlatformsStartTag;
	while (currentPlatformTag < kPlatformsStartTag + kNumPlatforms) {
		initPlatform();
		currentPlatformTag++;
	}
	resetPlatforms();
}

function initPlatform() {

	var platform;

	switch (random() % 2) {
	case 0:
		platform = Sprite.spriteWithSpriteFrame({
			frame : SpriteFrameCache.spriteFrameByName("platform1.png")
		});
		birdLayer.addChild(platform, 3, currentPlatformTag);
		break;
	case 1:
		platform = Sprite.spriteWithSpriteFrame({
			frame : SpriteFrameCache.spriteFrameByName("platform2.png")
		});
		birdLayer.addChild(platform, 3, currentPlatformTag);
		break;
	}
}

function resetPlatforms() {
	currentPlatformY = -1;
	currentPlatformTag = kPlatformsStartTag;
	currentMaxPlatformStep = 60.0;
	currentBonusPlatformIndex = 0;
	currentBonusType = 0;
	platformCount = 0;

	while (currentPlatformTag < kPlatformsStartTag + kNumPlatforms) {
		resetPlatform();
		currentPlatformTag++;
	}
}

function resetPlatform() {

	if (currentPlatformY < 0) {
		currentPlatformY = kStartingCurrentPlatformY;
	} else {
		currentPlatformY += random()
				% (currentMaxPlatformStep - kMinPlatformStep)
				+ kMinPlatformStep;

		if (currentMaxPlatformStep < kMaxPlatformStep) {
			currentMaxPlatformStep += 0.5;
		}
	}
	var platform = birdLayer.getChildByTag(currentPlatformTag);
	if (random() % 2 == 1)
		platform.setScaleX(-1.0);
	var x;
	var sizeW = platform.getContentSize().width;

	if (currentPlatformY == kStartingCurrentPlatformY) {
		x = screenWidth / 2;
	} else {
		x = random() % (screenWidth - sizeW) + sizeW / 2;
	}

	platform.setPosition(x, currentPlatformY);
	platformCount++;

	if (platformCount == currentBonusPlatformIndex) {
		var bonus = Sprite.cast(birdLayer.getChildByTag(kBonusStartTag
				+ currentBonusType));
		bonus.setPosition(x, currentPlatformY + 30);
		bonus.setIsVisible(true);
	}

}

function initBonus() {
	var bonus;
	for ( var i = 0; i < kNumBonuses; i++) {
		bonus = Sprite.spriteWithSpriteFrame({
			frame : SpriteFrameCache.spriteFrameByName(bonusImg[i])
		});
		birdLayer.addChild(bonus, 4, kBonusStartTag + i);
		bonus.setIsVisible(false);
	}
}

function initBirdLayer() {
	birdLayer = new Layer();
	var bird = Sprite.spriteWithSpriteFrame({
		frame : SpriteFrameCache.spriteFrameByName("bird.png")
	});
	birdLayer.addChild(bird, 4, kBird);
	var scoreLabel = new LabelBMFont({
		label : "0",
		fntFile : "img/bitmapFont.fnt"
	});
	birdLayer.addChild(scoreLabel, 5, kScoreLabel);
	scoreLabel.setPosition(screenWidth / 2, screenHegiht - 50);
	initPlatforms();
	initBonus();
}

function showtweejumpScene() {
	var game = new Scene();
	initCloundLayer();
	initBirdLayer();
	game.addChild(cloundLayer);
	game.addChild(birdLayer);
	SceneManager.changeTo(game);
}