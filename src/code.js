
// More API functions here:
// https://github.com/googlecreativelab/teachablemachine-community/tree/master/libraries/pose

// the link to your model provided by Teachable Machine export panel
const URL = "./model/";
let model, webcam, ctx, labelContainer, maxPredictions, audio;
let startTime, times, letterIndex = 0, pauseUntil = "";

document.getElementById("start").addEventListener("click", async () => {
	if (audio) {
		audio.pause();
	}

	const modelURL = URL + "model.json";
	const metadataURL = URL + "metadata.json";

	times = await (await fetch('./timestamps.json')).json()

	startTime = Date.now();
	audio = new Audio('./YMCA.mp3');
	audio.loop = true;
	audio.play();

	// load the model and metadata
	// Refer to tmImage.loadFromFiles() in the API to support files from a file picker
	// Note: the pose library adds a tmPose object to your window (window.tmPose)
	model = await tmPose.load(modelURL, metadataURL);
	maxPredictions = model.getTotalClasses();

	// Convenience function to setup a webcam
	const size = 200;
	const flip = true; // whether to flip the webcam
	webcam = new tmPose.Webcam(size, size, flip); // width, height, flip
	await webcam.setup(); // request access to the webcam
	await webcam.play();
	window.requestAnimationFrame(loop);

	// append/get elements to the DOM
	const canvas = document.getElementById("canvas");
	canvas.width = size; canvas.height = size;
	ctx = canvas.getContext("2d");
	labelContainer = document.getElementById("label-container");
	for (let i = 0; i < maxPredictions+1; i++) { // and class labels
		labelContainer.appendChild(document.createElement("div"));
	}
});

document.getElementById("stop").addEventListener("click", async () => {
	audio.pause();
});

async function loop(timestamp) {
	if (audio.currentTime * 1000 > times[letterIndex].time) {
		audio.pause();
		pauseUntil = times[letterIndex].letter
		labelContainer.childNodes[4].innerHTML = `Waiting for ${pauseUntil.toLocaleUpperCase()}`;
	}

	webcam.update(); // update the webcam frame
	const pred = await predict();

	if (pauseUntil.length > 0) {
		for (const p of pred) {
			if (p.className === pauseUntil && p.probability > 0.9) {
				audio.play();
				pauseUntil = '';
				letterIndex++;
				labelContainer.childNodes[4].innerHTML = "";
			}
		}
	}

	window.requestAnimationFrame(loop);
}

async function predict() {
	// Prediction #1: run input through posenet
	// estimatePose can take in an image, video or canvas html element
	const { pose, posenetOutput } = await model.estimatePose(webcam.canvas);
	// Prediction 2: run input through teachable machine classification model
	const prediction = await model.predict(posenetOutput);

	for (let i = 0; i < maxPredictions; i++) {
		const classPrediction =
			prediction[i].className + ": " + prediction[i].probability.toFixed(2);
		labelContainer.childNodes[i].innerHTML = classPrediction;
	}

	// finally draw the poses
	drawPose(pose);

	return prediction;
}

function drawPose(pose) {
	if (webcam.canvas) {
		ctx.drawImage(webcam.canvas, 0, 0);
		// draw the keypoints and skeleton
		if (pose) {
			const minPartConfidence = 0.5;
			tmPose.drawKeypoints(pose.keypoints, minPartConfidence, ctx);
			tmPose.drawSkeleton(pose.keypoints, minPartConfidence, ctx);
		}
	}
}
