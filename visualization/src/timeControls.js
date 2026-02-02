export class TimeControls {
    constructor(solarSystem) {
        this.solarSystem = solarSystem;
        
        /*--- Time state ---*/
        this.isPaused = false;
        this.timeScale = 1;  // 1 = 1 day per second
        this.lastTimestamp = performance.now();
        
        /*--- Time scale presets (days per second) ---*/
        this.scalePresets = [0.1, 0.5, 1, 5, 10, 30, 100, 365];
        this.currentPresetIndex = 2; // Start at 1x
        
        this.setupControls();
    }

    setupControls() {
        const btnPause = document.getElementById('btn-pause');
        const btnSlower = document.getElementById('btn-slower');
        const btnFaster = document.getElementById('btn-faster');
        const btnReset = document.getElementById('btn-reset');
        
        btnPause.addEventListener('click', () => this.togglePause());
        btnSlower.addEventListener('click', () => this.slower());
        btnFaster.addEventListener('click', () => this.faster());
        btnReset.addEventListener('click', () => this.reset());
        
        // Keyboard shortcuts
        window.addEventListener('keydown', (e) => {
            switch(e.key) {
                case ' ':
                    e.preventDefault();
                    this.togglePause();
                    break;
                case 'ArrowLeft':
                    this.slower();
                    break;
                case 'ArrowRight':
                    this.faster();
                    break;
                case 'r':
                case 'R':
                    this.reset();
                    break;
            }
        });
    }

    togglePause() {
        this.isPaused = !this.isPaused;
        const btn = document.getElementById('btn-pause');
        btn.textContent = this.isPaused ? '▶ Play' : '⏸ Pause';
        btn.classList.toggle('active', this.isPaused);
    }

    slower() {
        if (this.currentPresetIndex > 0) {
            this.currentPresetIndex--;
            this.timeScale = this.scalePresets[this.currentPresetIndex];
            this.updateScaleDisplay();
        }
    }

    faster() {
        if (this.currentPresetIndex < this.scalePresets.length - 1) {
            this.currentPresetIndex++;
            this.timeScale = this.scalePresets[this.currentPresetIndex];
            this.updateScaleDisplay();
        }
    }

    reset() {
        this.solarSystem.simulationTime = 0;
        this.timeScale = 1;
        this.currentPresetIndex = 2;
        this.isPaused = false;
        document.getElementById('btn-pause').textContent = '⏸ Pause';
        document.getElementById('btn-pause').classList.remove('active');
        this.updateScaleDisplay();
        this.updateDisplay();
    }

    getDeltaTime() {
        const now = performance.now();
        const dt = (now - this.lastTimestamp) / 1000; // seconds
        this.lastTimestamp = now;
        
        // Return simulation time delta (in seconds)
        // timeScale is in days per real second
        return dt * this.timeScale * 86400;
    }

    updateDisplay() {
        const totalDays = this.solarSystem.getSimulationDays();
        const years = Math.floor(totalDays / 365.25);
        const days = Math.floor(totalDays % 365.25);
        
        document.getElementById('current-date').textContent = `Year ${years}, Day ${days}`;
    }

    updateScaleDisplay() {
        const scale = this.scalePresets[this.currentPresetIndex];
        let scaleText;
        
        if (scale < 1) {
            scaleText = `${scale}x (${(scale * 24).toFixed(1)} hours/sec)`;
        } else if (scale === 1) {
            scaleText = '1x (1 day/sec)';
        } else if (scale < 365) {
            scaleText = `${scale}x (${scale} days/sec)`;
        } else {
            scaleText = `${scale}x (${(scale / 365.25).toFixed(1)} years/sec)`;
        }
        
        document.getElementById('time-scale').textContent = scaleText;
    }
}