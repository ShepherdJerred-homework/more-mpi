let numbers = [];
for (let i = 0; i < 64; i++) {
    numbers[i] = Math.floor(Math.random() * (10000 - 0) + 0);
}

let blur = [];
for (let i = 0; i < 64; i++) {
    if (i == 0) {
        blur[i] = (numbers[i] * 2 + numbers[i + 1]) / 3;
    } else if (i == 63) {
        blur[i] = (numbers[i - 1] + numbers[i] * 2) / 3;
    } else {
        blur[i] = (numbers[i - 1] + numbers[i] * 2 + numbers[i + 1]) / 4;
    }
}
