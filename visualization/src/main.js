import { Scene } from './scene.js';
import { SolarSystemRenderer } from './solarSystem.js';
import { TimeControls } from './timeControls.js';

class App {
    constructor() {
        this.scene = null;
        this.solarSystem = null;
        this.timeControls = null;
        this.isRunning = true;
    }

    async init() {
        try {
            // Initialize 3D scene
            this.scene = new Scene('canvas-container');
            
            // Load solar system data and create renderer
            this.solarSystem = new SolarSystemRenderer(this.scene);
            await this.solarSystem.loadData();
            
            // Initialize time controls
            this.timeControls = new TimeControls(this.solarSystem);
            
            // Hide loading
            document.getElementById('loading').classList.add('hidden');
            
            // Start animation loop
            this.animate();
            
            console.log('🌌 Solar System initialized successfully!');
        } catch (error) {
            console.error('Failed to initialize:', error);
            document.getElementById('loading').textContent = 'Error loading solar system';
        }
    }

    animate() {
        requestAnimationFrame(() => this.animate());
        
        if (this.isRunning && this.timeControls && !this.timeControls.isPaused) {
            const dt = this.timeControls.getDeltaTime();
            this.solarSystem.update(dt);
            this.timeControls.updateDisplay();
        }
        
        this.scene.render();
    }
}

// Start application
const app = new App();
app.init();