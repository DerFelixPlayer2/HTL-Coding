const URL = "./model/";
const modelURL = URL + "model.json";
const metadataURL = URL + "metadata.json";
window.modelURL = modelURL;
window.metadataURL = metadataURL;


let model, webcam, ctx, maxPredictions, audio, labelContainer, next_action, lds_ring;
let startTime, letterIndex = 0, pauseUntil = "";

let running = false;


document.addEventListener("DOMContentLoaded", async () => {
	webcam = new tmPose.Webcam(500, 500, true); // width, height, flip
	window.webcam = webcam;
	await webcam.setup(); // request access to the webcam
	await webcam.play();

	const canvas = document.getElementById("canvas")
	canvas.width = canvas.clientWidth;
	canvas.height = canvas.clientHeight;
	ctx = canvas.getContext("2d");
	labelContainer = document.getElementById("label-container");
	lds_ring = document.getElementById("lds-ring");
	next_action = document.getElementsByClassName("next-action")[0];

	window.requestAnimationFrame(loop);
});

document.getElementById("start").addEventListener("click", async () => {
	if (running) return;
	lds_ring.classList.remove("hidden");

	running = true;
	if (!startTime) startTime = Date.now();

	if (!audio) audio = new Audio('./YMCA.mp3');
	audio.play();

	if (!timestamps) timestamps = await (await fetch('./timestamps.json')).json()
	if (!model) { model = await tmPose.load(modelURL, metadataURL); window.model = model; }
	if (!maxPredictions) maxPredictions = model.getTotalClasses();

	lds_ring.classList.add("hidden");
	next_action.innerHTML = 'Playing';
});

document.getElementById("stop").addEventListener("click", () => {
	if (!running) return;
	running = false;
	audio.pause();
	next_action.innerHTML = 'Paused';
});

document.getElementById("start-test").addEventListener("click", () => {
	running = false;
	audio?.pause();

	setTimeout(() => {
		audio = null;
		startTime = null;
		pauseUntil = "";
		letterIndex = 0;
		next_action.innerHTML = '';
	}, 20);
});


async function predict() {
	const { pose, posenetOutput } = await model.estimatePose(webcam.canvas);
	const prediction = await model.predict(posenetOutput);

	getPredictionLabels().update(prediction);
	updateVideoKeypoints(pose);

	return prediction;
}

function getPredictionLabels() {
	return {
		update(predictions) {
			for (let i = 0, j = 0; i < predictions.length; j++) {
				if (labelContainer.childNodes[j].classList?.contains("perc")) {
					const p = predictions[i++];
					labelContainer.childNodes[j].innerHTML = p.probability.toFixed(2);
				}
			}
		},
		set(index, innerHTML) {
			for (let i = 0, j = 0; i <= index; j++) {
				if (labelContainer.childNodes[j].classList?.contains("perc") && i++ === index) {
					labelContainer.childNodes[j].innerHTML = innerHTML;
				}
			}
		}
	}
}

function updateVideoKeypoints(pose) {
	if (pose) {
		const minPartConfidence = 0.5;
		tmPose.drawKeypoints(pose.keypoints, minPartConfidence, ctx);
		tmPose.drawSkeleton(pose.keypoints, minPartConfidence, ctx);
	}
}

let timestamps;
async function loop() {
	webcam.update();
	if (webcam.canvas) ctx.drawImage(webcam.canvas, 0, 0);

	if (running && !!timestamps && !!model && !!audio) {
		if (audio.currentTime * 1000 > timestamps[letterIndex].time) {
			audio.pause();
			pauseUntil = timestamps[letterIndex].letter
			next_action.innerHTML = `Waiting for ${pauseUntil.toLocaleUpperCase()}`;
		}

		const pred = await predict();

		if (pauseUntil.length > 0) {
			for (const p of pred) {
				if (p.className === pauseUntil && p.probability > 0.9) {
					audio.play();
					pauseUntil = '';
					letterIndex++;
					next_action.innerHTML = `Playing`;
				}
			}
		}
	}

	window.requestAnimationFrame(loop);
}
