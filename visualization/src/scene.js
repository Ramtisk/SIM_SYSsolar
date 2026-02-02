export class Scene {
    constructor(containerId) {
        this.container = document.getElementById(containerId);
        
        /*--- Three.js core components ---*/
        this.scene = new THREE.Scene();
        this.camera = null;
        this.renderer = null;
        this.controls = null;
        
        /*--- Lighting ---*/
        this.lights = {};
        
        this.init();
    }

    init() {
        /*--- Camera setup ---*/
        const aspect = window.innerWidth / window.innerHeight;
        this.camera = new THREE.PerspectiveCamera(60, aspect, 0.1, 100000);
        this.camera.position.set(0, 500, 1000);
        this.camera.lookAt(0, 0, 0);

        /*--- Renderer setup ---*/
        this.renderer = new THREE.WebGLRenderer({ 
            antialias: true,
            alpha: true 
        });
        this.renderer.setSize(window.innerWidth, window.innerHeight);
        this.renderer.setPixelRatio(window.devicePixelRatio);
        this.renderer.setClearColor(0x000011, 1);
        this.container.appendChild(this.renderer.domElement);

        /*--- Orbit controls ---*/
        this.controls = new THREE.OrbitControls(this.camera, this.renderer.domElement);
        this.controls.enableDamping = true;
        this.controls.dampingFactor = 0.05;
        this.controls.minDistance = 10;
        this.controls.maxDistance = 50000;
        this.controls.enablePan = true;

        /*--- Lighting ---*/
        this.setupLighting();

        /*--- Starfield background ---*/
        this.createStarfield();

        /*--- Handle resize ---*/
        window.addEventListener('resize', () => this.onResize());
    }

    setupLighting() {
        // Ambient light (very dim)
        this.lights.ambient = new THREE.AmbientLight(0x222233, 0.3);
        this.scene.add(this.lights.ambient);

        // Point light at sun position
        this.lights.sun = new THREE.PointLight(0xffffff, 2, 10000);
        this.lights.sun.position.set(0, 0, 0);
        this.scene.add(this.lights.sun);
    }

    createStarfield() {
        const starsGeometry = new THREE.BufferGeometry();
        const starCount = 10000;
        const positions = new Float32Array(starCount * 3);
        const colors = new Float32Array(starCount * 3);

        for (let i = 0; i < starCount; i++) {
            // Random spherical distribution
            const radius = 20000 + Math.random() * 30000;
            const theta = Math.random() * Math.PI * 2;
            const phi = Math.acos(2 * Math.random() - 1);

            positions[i * 3] = radius * Math.sin(phi) * Math.cos(theta);
            positions[i * 3 + 1] = radius * Math.sin(phi) * Math.sin(theta);
            positions[i * 3 + 2] = radius * Math.cos(phi);

            // Random star colors (white, blue-white, yellow)
            const colorChoice = Math.random();
            if (colorChoice < 0.7) {
                colors[i * 3] = 1;
                colors[i * 3 + 1] = 1;
                colors[i * 3 + 2] = 1;
            } else if (colorChoice < 0.85) {
                colors[i * 3] = 0.8;
                colors[i * 3 + 1] = 0.9;
                colors[i * 3 + 2] = 1;
            } else {
                colors[i * 3] = 1;
                colors[i * 3 + 1] = 0.95;
                colors[i * 3 + 2] = 0.8;
            }
        }

        starsGeometry.setAttribute('position', new THREE.BufferAttribute(positions, 3));
        starsGeometry.setAttribute('color', new THREE.BufferAttribute(colors, 3));

        const starsMaterial = new THREE.PointsMaterial({
            size: 2,
            vertexColors: true,
            transparent: true,
            opacity: 0.8
        });

        const starField = new THREE.Points(starsGeometry, starsMaterial);
        this.scene.add(starField);
    }

    add(object) {
        this.scene.add(object);
    }

    remove(object) {
        this.scene.remove(object);
    }

    render() {
        this.controls.update();
        this.renderer.render(this.scene, this.camera);
    }

    onResize() {
        const width = window.innerWidth;
        const height = window.innerHeight;

        this.camera.aspect = width / height;
        this.camera.updateProjectionMatrix();
        this.renderer.setSize(width, height);
    }

    /*--- Camera utilities ---*/
    focusOn(position, distance = 100) {
        this.controls.target.copy(position);
        this.camera.position.set(
            position.x + distance,
            position.y + distance * 0.5,
            position.z + distance
        );
    }
}