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

  let n = 10;
  window.next_action.innerHTML = 'Testing ' + currentTest.toUpperCase() + '. ' +n+' more seconds.';
  const i2 = setInterval(() => {
    n--;
    window.next_action.innerHTML = 'Testing ' + currentTest.toUpperCase() + '. ' + n + ' more seconds.';
  }, 1000);

  setTimeout(() => {
    clearInterval(i);
    clearInterval(i2);

    window.next_action.innerHTML = '';
  }, 10000);
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

function updateMatrix(matrix, dtp, dfp, dfn, dtn) {
  const tp = parseInt(matrix.getElementsByClassName("tp")[0].innerHTML);
  const fp = parseInt(matrix.getElementsByClassName("fp")[0].innerHTML);
  const fn = parseInt(matrix.getElementsByClassName("fn")[0].innerHTML);
  const tn = parseInt(matrix.getElementsByClassName("tn")[0].innerHTML);

  matrix.getElementsByClassName("tp")[0].innerHTML = tp + dtp;
  matrix.getElementsByClassName("fp")[0].innerHTML = fp + dfp;
  matrix.getElementsByClassName("fn")[0].innerHTML = fn + dfn;
  matrix.getElementsByClassName("tn")[0].innerHTML = tn + dtn;

  const accuracy = (tp + tn) / (tp + tn + fp + fn);
  const precision = tp / (tp + fp);
  const recall = tp / (tp + fn);
  const f1 = 2 * precision * recall / (precision + recall);

  matrix.getElementsByClassName("a")[0].innerHTML = accuracy.toFixed(2);
  matrix.getElementsByClassName("p")[0].innerHTML = precision.toFixed(2);
  matrix.getElementsByClassName("r")[0].innerHTML = recall.toFixed(2);
  matrix.getElementsByClassName("f")[0].innerHTML = f1.toFixed(2);
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
