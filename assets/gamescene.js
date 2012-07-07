var gameScene;
var heroSprite;
var fightSprite;
var npcSprite;
var teleportSprite;
var iconWidth = 32;
var fightAnimation;
var npcAnimation;
var currentDirection = 0;
var mapSizeHeight;
var mapSizeWidth;
var tileSizeHeight;
var tileSizeWidth;
var map;
var gameLayer;
var isWalking = false;
var isFighting = false;
var isOpening = false;
var doorId;
var tipOrder = 4;
var wallLayer;
var enemyLayer;
var itemLayer;
var doorLayer;
var titleMapPositionX;
var titleMapPositionY;
var npcIndexArray;
var teleportIndexArray;
var heroTileCoordX = 1;
var heroTileCoordY = 11;
var targetMap = 1;
var opendoorCallbackId;
function setFaceDirection() {
	heroSprite.setTextureRect(0, 32 * currentDirection, 32, 32);

}
function onRunActionDone() {
	setFaceDirection();
	setSecenPosition();
	isWalking = false;
}

function OnGameScheduleCallback(dt) {
	if (isWalking) {
		setSecenPosition();
	}
}

function setSecenPosition() {
	var spritePosition = heroSprite.getPosition();
	var spritePositionY = spritePosition.y;
	var spritePositionX = spritePosition.x;
	var halfOfWidth = screenWidth / 2.0;
	var halfOfHeight = screenHegiht / 2.0;
	var x = spritePositionX > halfOfWidth ? spritePositionX : halfOfWidth;
	var y = spritePositionY > halfOfHeight ? spritePositionY : halfOfHeight;
	var subWidth = mapSizeWidth * tileSizeWidth - halfOfWidth;
	var subHeight = mapSizeHeight * tileSizeHeight - halfOfHeight
	if (mapSizeWidth > screenWidth) {
		x = x > subHeight ? subHeight : x;
	}
	if (mapSizeHeight > screenHegiht) {
		y = y > subHeight ? subHeight : y;
	}
	var actualX = halfOfWidth - x;
	var actualY = halfOfHeight - y;
	gameLayer.setPosition(actualX, actualY);
}

function tileCoordXForPosition(x) {
	return x / tileSizeWidth;
}

function tileCoordYForPosition(y) {
	return (((mapSizeHeight - 1) * tileSizeHeight) - y) / tileSizeHeight;
}

function positionYForTileCoord(y) {
	return (mapSizeHeight - y - 1) * tileSizeHeight;
}

function positionXForTileCoord(x) {
	return x * tileSizeWidth;
}

function onTipCallback() {
	gameLayer.removeFromParentAndCleanup(tipOrder, true);
}

function showTip(tip, positionX, positionY) {
	var tipLabel = new LabelTTF({
		label : tip,
		fontName : "Arial",
		fontSize : 20
	});
	tipLabel.setPosition(positionX + 16, positionY + 16);
	gameLayer.addChild(tipLabel, tipOrder, tipOrder);
	var move = new MoveBy({
		duration : 0.5,
		point : new Point({
			x : 0,
			y : 32
		})
	});
	var delay = new DelayTime({
		duration : 0.5
	});
	var fadeOut = new FadeOut({
		duration : 0.2
	});
	var callbackAction = new CallFunc({
		handler : onTipCallback
	});
	var sequence = new Sequence({
		move : move,
		delay : delay,
		fadeOut : fadeOut,
		callback : callbackAction
	});
	tipLabel.runAction(sequence);

}
function OnSpriteScheduleCallback(dt) {
	var nextGID = doorLayer.tileGIDAt(titleMapPositionX, titleMapPositionY) + 4;
	if (nextGID - doorId > 4 * 3) {
		doorLayer.removeTileAt(titleMapPositionX, titleMapPositionY);
		unschedule(opendoorCallbackId);
		isOpening = false;
	} else {
		doorLayer.setTileGID(nextGID, titleMapPositionX, titleMapPositionY);
	}
}
function openDoor(gid) {
	if (isOpening) {
		return;
	}
	doorId = gid;
	isOpening = true;
	opendoorCallbackId = schedule(OnSpriteScheduleCallback, 0.1);
}

function onFightDone() {
	isFighting = false;
	fightSprite.setIsVisible(false);
	enemyLayer.removeTileAt(titleMapPositionX, titleMapPositionY);
}

function fight(positionX, positionY) {
	if (isFighting)
		return;
	isFighting = true;
	var spritePosition = heroSprite.getPosition();
	var spritePositionX = spritePosition.x;
	var spritePositionY = spritePosition.y;
	showTip("lost hp -100", spritePositionX, spritePositionY);
	fightSprite.setIsVisible(true);
	var targetX = 0;
	var targetY = 0;
	if (positionX == spritePositionX) {
		targetX = positionX;
	} else {
		targetX = positionX > spritePositionX ? (positionX - spritePositionX)
				/ 2 + spritePositionX : (spritePositionX - positionX) / 2
				+ positionX
	}
	if (positionY == spritePositionY) {
		targetY = positionY;
	} else {
		targetY = positionY > spritePositionY ? (positionY - spritePositionY)
				/ 2 + spritePositionY : (spritePositionY - positionY) / 2
				+ positionY
	}
	fightSprite.setPosition(targetX, targetY);
	var animate = new Animate({
		animation : createFightAnimation(),
		restoreFrame : true
	});
	var callbackAction = new CallFunc({
		handler : onFightDone
	});
	var sequence = new Sequence({
		animate : animate,
		callback : callbackAction
	});
	fightSprite.runAction(sequence);
}

function pickUpItem() {
	var spritePosition = heroSprite.getPosition();
	var spritePositionY = spritePosition.y;
	var spritePositionX = spritePosition.x;
	showTip("get item, hp +100", spritePositionX, spritePositionY);
	itemLayer.removeTileAt(titleMapPositionX, titleMapPositionY);
}

function talkWithNPC() {
	var spritePosition = heroSprite.getPosition();
	var spritePositionY = spritePosition.y;
	var spritePositionX = spritePosition.x;
	showTip("hi,you are so pretty!!!", spritePositionX, spritePositionY);
}

function removeFadeLayer() {
	gameScene.removeChildByTag(2, true);
}
function resetGameLayer() {
	gameScene.removeChildByTag(0, true);
	initGameLayer();
	gameScene.addChild(gameLayer, 0, 0);
	var fadeOut = new FadeOut({
		duration : 0.5
	});
	var callbackAction = new CallFunc({
		handler : removeFadeLayer
	});
	var action = new Sequence({
		fadeOut : fadeOut,
		callback : callbackAction
	});
	layerColor.runAction(action);
}

function switchMap() {
	layerColor = new LayerColor({
		color : ccc4(0, 0, 0, 0)
	});
	layerColor.setPosition(0, 0);
	layerColor.setAnchorPoint(0, 0);
	gameScene.addChild(layerColor, 2, 2);
	var fadeIn = new FadeIn({
		duration : 0.5
	});
	var callbackAction = new CallFunc({
		handler : resetGameLayer
	});
	var action = new Sequence({
		fadeIn : fadeIn,
		callback : callbackAction
	});
	layerColor.runAction(action);
}

function checkCollision(positionX, positionY) {
	titleMapPositionX = tileCoordXForPosition(positionX);
	titleMapPositionY = tileCoordYForPosition(positionY);
	if (titleMapPositionX < 0 || titleMapPositionX > mapSizeWidth - 1
			|| titleMapPositionY < 0 || titleMapPositionY > mapSizeHeight - 1)
		return true;

	var targetId = wallLayer.tileGIDAt(titleMapPositionX, titleMapPositionY);

	if (targetId > 0) {
		return true;
	}
	targetId = enemyLayer.tileGIDAt(titleMapPositionX, titleMapPositionY);
	if (targetId > 0) {
		fight(positionX, positionY);
		return true;
	}
	targetId = itemLayer.tileGIDAt(titleMapPositionX, titleMapPositionY);
	if (targetId > 0) {
		pickUpItem();
		return false;
	}
	targetId = doorLayer.tileGIDAt(titleMapPositionX, titleMapPositionY);
	if (targetId > 0) {
		openDoor(targetId);
		return true;
	}
	var index = titleMapPositionX + titleMapPositionY * mapSizeWidth;
	if (npcIndexArray.indexOf(index) != -1) {
		talkWithNPC();
		return true;
	}
	if (teleportIndexArray.indexOf(index) != -1) {
		switchMap();
		return true;
	}
	return false;

}

function createFightAnimation() {
	var fightOrder = new Array(4, 6, 8, 10, 13, 15, 17, 19, 20, 22);
	var fightTexture = new Texture2D({
		fileName : "img/sword.png"
	});
	var frame;
	var frameArray = new Array();
	var x, y;
	for ( var i = 0; i < 10; i++) {
		x = fightOrder[i] % 5 - 1;
		y = fightOrder[i] / 5;

		frame = new SpriteFrame({
			texture : fightTexture,
			rect : new Rect({
				x : 192 * x,
				y : 192 * y,
				width : 192,
				height : 192
			})
		});
		if (fightOrder[i] == 17 || fightOrder[i] == 19) {
			frame.setOffsetInPixels(0, -8);
		}
		frameArray.push(frame);
	}
	return new Animation({
		frames : frameArray,
		delay : 0.1
	});
}

function createNPCAnimation() {

	var npcTexture = new Texture2D({
		fileName : "img/npc.png"
	});
	var frameArray = new Array();
	for ( var i = 0; i < 4; i++) {
		var frame = new SpriteFrame({
			texture : npcTexture,
			rect : new Rect({
				x : 32 * i,
				y : 0,
				width : 32,
				height : 32
			})
		});
		frameArray.push(frame);
	}
	return new Animation({
		frames : frameArray,
		delay : 0.2
	});
}

function createAnimationByDirection(direction) {

	var heroTexture = new Texture2D({
		fileName : "img/hero.png"
	});
	var frameArray = new Array();
	for ( var i = 0; i < 4; i++) {
		var frame = new SpriteFrame({
			texture : heroTexture,
			rect : new Rect({
				x : 32 * i,
				y : 32 * direction,
				width : 32,
				height : 32
			})
		});
		frameArray.push(frame);
	}
	return new Animation({
		frames : frameArray,
		delay : 0.07
	});
}

function onActionChange(moveX, moveY) {
	var spritePosition = heroSprite.getPosition();
	var ishasCollision = checkCollision(spritePosition.x + moveX,
			spritePosition.y + moveY);
	if (ishasCollision) {
		setFaceDirection();
		return;
	}
	var animate = new Animate({
		animation : createAnimationByDirection(currentDirection),
		restoreFrame : false
	});
	var move = new MoveBy({
		duration : 0.28,
		point : new Point({
			x : moveX,
			y : moveY
		})
	});
	var spawn = new Spawn({
		animate : animate,
		move : move
	});
	var callbackAction = new CallFunc({
		handler : onRunActionDone
	});
	var sequence = new Sequence({
		spawn : spawn,
		callback : callbackAction
	});
	heroSprite.runAction(sequence);
	isWalking = true;
}

function heroSpriteDown(item) {
	if (isWalking)
		return;
	currentDirection = 0;
	onActionChange(0, iconWidth * -1);
}

function heroSpriteUp(item) {
	if (isWalking)
		return;
	currentDirection = 3;
	onActionChange(0, iconWidth);
}

function heroSpriteRight(item) {
	if (isWalking)
		return;
	currentDirection = 2;
	onActionChange(iconWidth, 0);
}

function heroSpriteLeft(item) {
	if (isWalking)
		return;
	currentDirection = 1;
	onActionChange(iconWidth * -1, 0);
}

function initNPCandTeleport(map) {
	var group = map.objectGroupNamed("object");
	var objects = group.getObjects();
	if (objects) {
		var x = 0;
		var y = 0;
		var type = "";
		for ( var i = 0; i < objects.length; i++) {
			x = objects[i].getIntValue("x");
			y = objects[i].getIntValue("y");
			type = objects[i].getStringValue("type");
			var tilePositionX = tileCoordXForPosition(x);
			var tilePositionY = tileCoordYForPosition(y);
			var index = tilePositionX + tilePositionY * mapSizeWidth;
			if (type == "teleport") {
				teleportIndexArray.push(index);
				heroTileCoordX = objects[i].getIntValue("heroTileCoordX");
				heroTileCoordY = objects[i].getIntValue("heroTileCoordY");
				targetMap = objects[i].getIntValue("targetMap");
				teleportSprite = Sprite.spriteWithFile({
					fileName : "img/down_floor.png"
				});
				teleportSprite.setAnchorPoint(0, 0);
				teleportSprite.setPosition(x, y);
				gameLayer.addChild(teleportSprite, 2);
			} else if (type == "npc") {
				var npcId = objects[i].getStringValue("name");
				var x1 = objects[i].getIntValue("rectX");
				var y1 = objects[i].getIntValue("rectY");
				npcSprite = Sprite.spriteWithFile({
					fileName : "img/npc.png",
					rect : new Rect({
						x : x1,
						y : y1,
						width : 32,
						height : 32
					})
				});
				npcSprite.setAnchorPoint(0, 0);
				npcSprite.setPosition(x, y);
				gameLayer.addChild(npcSprite, 1);
				npcIndexArray.push(index);
				var animate = new Animate({
					animation : createNPCAnimation(),
					restoreFrame : true
				});
				var action = new RepeatForever({
					action : animate
				});
				npcSprite.runAction(action);
			}
		}
	}
}

function initGameLayer() {
	gameLayer = new Layer();
	schedule(OnGameScheduleCallback, 0);
	map = new TMXTiledMap({
		mapFile : "img/" + targetMap + ".tmx"
	});
	wallLayer = map.layerNamed("wall");
	itemLayer = map.layerNamed("item");
	enemyLayer = map.layerNamed("enemy");
	doorLayer = map.layerNamed("door");
	mapSizeHeight = map.getMapSize().height;
	mapSizeWidth = map.getMapSize().width;
	tileSizeHeight = map.getTileSize().height;
	tileSizeWidth = map.getTileSize().width;
	npcIndexArray = new Array();
	teleportIndexArray = new Array();
	initNPCandTeleport(map);

	var spriteFarme = createAnimationByDirection(0).getSpriteFrame(0);
	heroSprite = Sprite.spriteWithSpriteFrame({
		frame : spriteFarme
	});
	heroSprite.setAnchorPoint(0, 0);
	var spriteX = positionXForTileCoord(heroTileCoordX);
	var spriteY = positionYForTileCoord(heroTileCoordY);
	heroSprite.setPosition(spriteX, spriteY);
	fightSprite = new Sprite({
		fileName : "img/transparent.png"
	});
	fightSprite.setPosition(0, 0);
	fightSprite.setIsVisible(false);
	fightSprite.setAnchorPoint(0.5, 0.5);
	gameLayer.addChild(map, 0);
	gameLayer.addChild(heroSprite, 0);
	gameLayer.addChild(fightSprite, 1);

}

function initCotrollLayer() {
	var down = new MenuItemImage({
		normalImage : "img/down.png",
		selectedImage : "img/down.png",
		handler : heroSpriteDown
	});
	var left = new MenuItemImage({
		normalImage : "img/left.png",
		selectedImage : "img/left.png",
		handler : heroSpriteLeft
	});
	var right = new MenuItemImage({
		normalImage : "img/right.png",
		selectedImage : "img/right.png",
		handler : heroSpriteRight
	});
	var up = new MenuItemImage({
		normalImage : "img/up.png",
		selectedImage : "img/up.png",
		handler : heroSpriteUp
	});
	var mainScene = new MenuItemFont({
		title : "mainScene",
		handler : showsceneOne
	});
	mainScene.setPosition(screenWidth - 20, 20);
	var mainMenu = new Menu({
		item : mainScene
	});
	mainMenu.setPosition(0, 0);
	var directionMenus = new Menu({
		item1 : left,
		item2 : down,
		item3 : up,
		item4 : right
	});
	left.setPosition(screenWidth - 82, screenHegiht - 65);
	down.setPosition(screenWidth - 52, screenHegiht - 100);
	up.setPosition(screenWidth - 52, screenHegiht - 30);
	right.setPosition(screenWidth - 22, screenHegiht - 65);

	directionMenus.setPosition(0, 0);
	gameScene.controlPanel().addChild(mainMenu, 0);
	gameScene.controlPanel().addChild(directionMenus, 0);
}
function showGameScene() {

	gameScene = new Scene();
	initCotrollLayer();
	initGameLayer();

	gameScene.addChild(gameLayer, 0, 0);
	gameScene.setPosition(100, 2);
	SceneManager.changeTo(gameScene, TransitionScene.flipX, 1.2);
}
