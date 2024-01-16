let currentTest = '', matrixY, matrixM, matrixC, matrixA;

document.getElementById("start-test").addEventListener("click", async () => {
  document.getElementById("start-test").classList.add("hidden");
  document.getElementsByClassName("inner-container")[0].classList.add("hidden");
  document.getElementsByClassName("grid-container")[0].classList.add("hidden");
  
  document.getElementsByClassName("inner-container")[1].classList.remove("hidden");
  document.getElementsByClassName("accuracy")[0].classList.remove("hidden");

  if (!model) { model = await tmPose.load(window.modelURL, window.metadataURL); window.model = model; }
  
  matrixY = document.getElementsByClassName("confusion-matrix-y")[0];
  matrixM = document.getElementsByClassName("confusion-matrix-m")[0];
  matrixC = document.getElementsByClassName("confusion-matrix-c")[0];
  matrixA = document.getElementsByClassName("confusion-matrix-a")[0];
});

document.getElementById("test-y").addEventListener("click", async () => {
  currentTest = 'y';
  runTest();
});
document.getElementById("test-m").addEventListener("click", async () => {
  currentTest = 'm';
  runTest();
});
document.getElementById("test-c").addEventListener("click", async () => {
  currentTest = 'c';
  runTest();
});
document.getElementById("test-a").addEventListener("click", async () => {
  currentTest = 'a';
  runTest();
});

async function runTest() {
  await count_down();

  const i = setInterval(async () => {
    window.webcam.update();
    
    const { pose, posenetOutput } = await window.model.estimatePose(webcam.canvas);
    const prediction = await window.model.predict(posenetOutput);

    updateVideoKeypoints(pose);
    updateAccuracy(prediction);
  }, 1000 / 30);

  setTimeout(() => clearInterval(i), 10000);
}

function updateAccuracy(prediction) {

  if (prediction[0].probability > 0.9) { // predict y
    switch (currentTest) {
      case 'y':
        updateMatrix(matrixY, 1, 0, 0, 0);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'm':
        updateMatrix(matrixY, 0, 1, 0, 0);
        updateMatrix(matrixM, 0, 0, 1, 0);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'c':
        updateMatrix(matrixY, 0, 1, 0, 0);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 0, 1, 0);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'a':
        updateMatrix(matrixY, 0, 1, 0, 0);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 0, 1, 0);
        break;
    }
  } else if (prediction[1].probability > 0.9) { // predict m
    switch (currentTest) {
      case 'y':
        updateMatrix(matrixY, 0, 0, 1, 0);
        updateMatrix(matrixM, 0, 1, 0, 0);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'm':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 1, 0, 0, 0);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'c':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 1, 0, 0);
        updateMatrix(matrixC, 0, 0, 1, 0);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'a':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 1, 0, 0);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 0, 1, 0);
        break;
    }
  } else if (prediction[2].probability > 0.9) { // predict c
    switch (currentTest) {
      case 'y':
        updateMatrix(matrixY, 0, 0, 1, 0);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 1, 0, 0);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'm':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 0, 1, 0);
        updateMatrix(matrixC, 0, 1, 0, 0);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'c':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 1, 0, 0, 0);
        updateMatrix(matrixA, 0, 0, 0, 1);
        break;
      case 'a':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 1, 0, 0);
        updateMatrix(matrixA, 0, 0, 1, 0);
        break;
    }
  } else if (prediction[3].probability > 0.9) { // predict a
    switch (currentTest) {
      case 'y':
        updateMatrix(matrixY, 0, 0, 1, 0);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 1, 0, 0);
        break;
      case 'm':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 0, 1, 0);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 0, 1, 0, 0);
        break;
      case 'c':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 0, 1, 0);
        updateMatrix(matrixA, 0, 1, 0, 0);
        break;
      case 'a':
        updateMatrix(matrixY, 0, 0, 0, 1);
        updateMatrix(matrixM, 0, 0, 0, 1);
        updateMatrix(matrixC, 0, 0, 0, 1);
        updateMatrix(matrixA, 1, 0, 0, 0);
        break;
    }
  }

}

function updateMatrix(matrix, tp, fp, fn, tn) {
  matrix.getElementsByClassName("tp")[0].innerHTML = parseInt(matrix.getElementsByClassName("tp")[0].innerHTML) + tp;
  matrix.getElementsByClassName("fp")[0].innerHTML = parseInt(matrix.getElementsByClassName("fp")[0].innerHTML) + fp;
  matrix.getElementsByClassName("fn")[0].innerHTML = parseInt(matrix.getElementsByClassName("fn")[0].innerHTML) + fn;
  matrix.getElementsByClassName("tn")[0].innerHTML = parseInt(matrix.getElementsByClassName("tn")[0].innerHTML) + tn;
}

function updateVideoKeypoints(pose) {
	if (pose) {
		const minPartConfidence = 0.5;
		tmPose.drawKeypoints(pose.keypoints, minPartConfidence, ctx);
		tmPose.drawSkeleton(pose.keypoints, minPartConfidence, ctx);
	}
}

async function count_down() {
  const count_down = document.getElementById("count-down");
  count_down.innerHTML = "3";
  await sleep(1000);
  count_down.innerHTML = "2";
  await sleep(1000);
  count_down.innerHTML = "1";
  await sleep(1000);
  count_down.innerHTML = "0";
  await sleep(1000);
  count_down.innerHTML = "";
}

async function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}
