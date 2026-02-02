export class SolarSystemRenderer {
    constructor(scene) {
        this.scene = scene;
        
        /*--- Celestial bodies ---*/
        this.sun = null;
        this.planets = [];
        this.moons = [];
        
        /*--- Data ---*/
        this.planetData = [];
        this.moonData = [];
        
        /*--- Simulation state ---*/
        this.simulationTime = 0;  // seconds since epoch
        
        /*--- Scale factors (for visualization) ---*/
        this.distanceScale = 1 / 1e9;    // 1 unit = 1 billion meters
        this.sizeScale = 1 / 1e7;         // 1 unit = 10 million meters
        this.sunSizeScale = 1 / 1e8;      // Sun is scaled down more
        
        /*--- Raycaster for selection ---*/
        this.raycaster = new THREE.Raycaster();
        this.mouse = new THREE.Vector2();
        this.selectedBody = null;
        
        this.setupInteraction();
    }

    async loadData() {
        try {
            // Load planet data
            const planetResponse = await fetch('../data/solar-system/planet.json');
            this.planetData = await planetResponse.json();
            
            // Load moon data
            const moonResponse = await fetch('../data/solar-system/moons.json');
            this.moonData = await moonResponse.json();
            
            // Create celestial bodies
            this.createSun();
            this.createPlanets();
            this.createMoons();
            this.createOrbitLines();
            
            console.log(`Loaded ${this.planets.length} planets and ${this.moons.length} moons`);
        } catch (error) {
            console.error('Error loading solar system data:', error);
            // Create default solar system if data loading fails
            this.createDefaultSolarSystem();
        }
    }

    createSun() {
        const sunRadius = 6.96e8 * this.sunSizeScale;
        
        // Sun geometry
        const geometry = new THREE.SphereGeometry(sunRadius, 64, 64);
        
        // Sun material with glow effect
        const material = new THREE.MeshBasicMaterial({
            color: 0xffdd44,
            transparent: true,
            opacity: 1
        });
        
        this.sun = new THREE.Mesh(geometry, material);
        this.sun.userData = {
            name: 'Sun',
            type: 'star',
            mass: 1.989e30,
            radius: 6.96e8
        };
        
        // Add glow effect
        const glowGeometry = new THREE.SphereGeometry(sunRadius * 1.2, 32, 32);
        const glowMaterial = new THREE.MeshBasicMaterial({
            color: 0xffaa00,
            transparent: true,
            opacity: 0.3,
            side: THREE.BackSide
        });
        const glow = new THREE.Mesh(glowGeometry, glowMaterial);
        this.sun.add(glow);
        
        this.scene.add(this.sun);
    }

    createPlanets() {
        const defaultPlanets = [
            { name: 'Mercury', color: 0x8c7853, radius: 2.44e6, semiMajorAxis: 5.79e10, eccentricity: 0.206, orbitalPeriod: 88 * 86400 },
            { name: 'Venus', color: 0xffc649, radius: 6.05e6, semiMajorAxis: 1.082e11, eccentricity: 0.007, orbitalPeriod: 225 * 86400 },
            { name: 'Earth', color: 0x6b93d6, radius: 6.371e6, semiMajorAxis: 1.496e11, eccentricity: 0.017, orbitalPeriod: 365.25 * 86400 },
            { name: 'Mars', color: 0xc1440e, radius: 3.39e6, semiMajorAxis: 2.279e11, eccentricity: 0.093, orbitalPeriod: 687 * 86400 },
            { name: 'Jupiter', color: 0xd8ca9d, radius: 6.99e7, semiMajorAxis: 7.785e11, eccentricity: 0.049, orbitalPeriod: 4333 * 86400 },
            { name: 'Saturn', color: 0xead6b8, radius: 5.82e7, semiMajorAxis: 1.432e12, eccentricity: 0.056, orbitalPeriod: 10759 * 86400 },
            { name: 'Uranus', color: 0xd1e7e7, radius: 2.54e7, semiMajorAxis: 2.867e12, eccentricity: 0.046, orbitalPeriod: 30687 * 86400 },
            { name: 'Neptune', color: 0x5b5ddf, radius: 2.46e7, semiMajorAxis: 4.515e12, eccentricity: 0.010, orbitalPeriod: 60190 * 86400 }
        ];

        const planetsToUse = this.planetData.length > 0 ? this.planetData : defaultPlanets;

        for (const data of planetsToUse) {
            const planet = this.createPlanetMesh(data);
            this.planets.push(planet);
            this.scene.add(planet);
        }
    }

    createPlanetMesh(data) {
        // Scale radius for visibility (minimum size for small planets)
        let visualRadius = data.radius * this.sizeScale;
        visualRadius = Math.max(visualRadius, 2); // Minimum 2 units
        
        const geometry = new THREE.SphereGeometry(visualRadius, 32, 32);
        const material = new THREE.MeshStandardMaterial({
            color: data.color || 0x888888,
            roughness: 0.8,
            metalness: 0.1
        });
        
        const mesh = new THREE.Mesh(geometry, material);
        
        // Store orbital data
        mesh.userData = {
            name: data.name,
            type: 'planet',
            mass: data.mass || 0,
            radius: data.radius,
            semiMajorAxis: data.semiMajorAxis,
            eccentricity: data.eccentricity || 0,
            orbitalPeriod: data.orbitalPeriod,
            inclination: data.inclination || 0,
            meanAnomaly: Math.random() * Math.PI * 2 // Random starting position
        };
        
        // Set initial position
        this.updatePlanetPosition(mesh, 0);
        
        return mesh;
    }

    createMoons() {
        // Moons would be created similarly, orbiting their parent planets
        // For now, just add Earth's Moon as example
        const moonData = {
            name: 'Moon',
            color: 0xaaaaaa,
            radius: 1.737e6,
            semiMajorAxis: 3.844e8,
            eccentricity: 0.0549,
            orbitalPeriod: 27.3 * 86400,
            parentPlanet: 'Earth'
        };
        
        const moon = this.createMoonMesh(moonData);
        if (moon) {
            this.moons.push(moon);
            this.scene.add(moon);
        }
    }

    createMoonMesh(data) {
        const parentPlanet = this.planets.find(p => p.userData.name === data.parentPlanet);
        if (!parentPlanet) return null;
        
        let visualRadius = data.radius * this.sizeScale;
        visualRadius = Math.max(visualRadius, 1);
        
        const geometry = new THREE.SphereGeometry(visualRadius, 16, 16);
        const material = new THREE.MeshStandardMaterial({
            color: data.color || 0x888888,
            roughness: 0.9,
            metalness: 0
        });
        
        const mesh = new THREE.Mesh(geometry, material);
        
        mesh.userData = {
            name: data.name,
            type: 'moon',
            parentPlanet: parentPlanet,
            semiMajorAxis: data.semiMajorAxis,
            eccentricity: data.eccentricity || 0,
            orbitalPeriod: data.orbitalPeriod,
            meanAnomaly: Math.random() * Math.PI * 2
        };
        
        return mesh;
    }

    createOrbitLines() {
        for (const planet of this.planets) {
            const orbitLine = this.createOrbitLine(planet.userData);
            this.scene.add(orbitLine);
        }
    }

    createOrbitLine(orbitalData) {
        const points = [];
        const segments = 128;
        const a = orbitalData.semiMajorAxis * this.distanceScale;
        const e = orbitalData.eccentricity || 0;
        
        for (let i = 0; i <= segments; i++) {
            const theta = (i / segments) * Math.PI * 2;
            const r = a * (1 - e * e) / (1 + e * Math.cos(theta));
            
            const x = r * Math.cos(theta);
            const z = r * Math.sin(theta);
            
            points.push(new THREE.Vector3(x, 0, z));
        }
        
        const geometry = new THREE.BufferGeometry().setFromPoints(points);
        const material = new THREE.LineBasicMaterial({
            color: 0x444466,
            transparent: true,
            opacity: 0.4
        });
        
        return new THREE.Line(geometry, material);
    }

    updatePlanetPosition(planet, time) {
        const data = planet.userData;
        const a = data.semiMajorAxis * this.distanceScale;
        const e = data.eccentricity || 0;
        const T = data.orbitalPeriod;
        
        // Calculate mean anomaly
        const n = (2 * Math.PI) / T; // mean motion
        const M = data.meanAnomaly + n * time;
        
        // Solve Kepler's equation (simple iteration)
        let E = M;
        for (let i = 0; i < 10; i++) {
            E = M + e * Math.sin(E);
        }
        
        // True anomaly
        const nu = 2 * Math.atan2(
            Math.sqrt(1 + e) * Math.sin(E / 2),
            Math.sqrt(1 - e) * Math.cos(E / 2)
        );
        
        // Radius
        const r = a * (1 - e * Math.cos(E));
        
        // Position
        planet.position.x = r * Math.cos(nu);
        planet.position.z = r * Math.sin(nu);
        planet.position.y = 0; // Ignoring inclination for now
    }

    updateMoonPosition(moon, time) {
        const data = moon.userData;
        const parent = data.parentPlanet;
        
        if (!parent) return;
        
        // Moon orbit relative to parent (scaled up for visibility)
        const a = data.semiMajorAxis * this.distanceScale * 10; // Scale up moon orbits
        const e = data.eccentricity || 0;
        const T = data.orbitalPeriod;
        
        const n = (2 * Math.PI) / T;
        const M = data.meanAnomaly + n * time;
        
        let E = M;
        for (let i = 0; i < 10; i++) {
            E = M + e * Math.sin(E);
        }
        
        const nu = 2 * Math.atan2(
            Math.sqrt(1 + e) * Math.sin(E / 2),
            Math.sqrt(1 - e) * Math.cos(E / 2)
        );
        
        const r = a * (1 - e * Math.cos(E));
        
        // Position relative to parent
        moon.position.x = parent.position.x + r * Math.cos(nu);
        moon.position.z = parent.position.z + r * Math.sin(nu);
        moon.position.y = parent.position.y;
    }

    update(dt) {
        this.simulationTime += dt;
        
        // Rotate sun
        if (this.sun) {
            this.sun.rotation.y += 0.001;
        }
        
        // Update planet positions
        for (const planet of this.planets) {
            this.updatePlanetPosition(planet, this.simulationTime);
            planet.rotation.y += 0.01; // Planet rotation
        }
        
        // Update moon positions
        for (const moon of this.moons) {
            this.updateMoonPosition(moon, this.simulationTime);
        }
    }

    setupInteraction() {
        window.addEventListener('click', (event) => this.onMouseClick(event));
    }

    onMouseClick(event) {
        this.mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
        this.mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;
        
        this.raycaster.setFromCamera(this.mouse, this.scene.camera);
        
        const allBodies = [this.sun, ...this.planets, ...this.moons].filter(b => b);
        const intersects = this.raycaster.intersectObjects(allBodies);
        
        if (intersects.length > 0) {
            this.selectBody(intersects[0].object);
        }
    }

    selectBody(body) {
        this.selectedBody = body;
        const data = body.userData;
        
        // Update info panel
        document.getElementById('body-name').textContent = data.name || 'Unknown';
        document.getElementById('body-mass').textContent = data.mass ? `${data.mass.toExponential(2)} kg` : '-';
        document.getElementById('body-radius').textContent = data.radius ? `${(data.radius / 1000).toFixed(0)} km` : '-';
        
        if (data.semiMajorAxis) {
            const au = data.semiMajorAxis / 1.496e11;
            document.getElementById('body-distance').textContent = `${au.toFixed(2)} AU`;
        } else {
            document.getElementById('body-distance').textContent = '0 (center)';
        }
        
        if (data.orbitalPeriod) {
            const years = data.orbitalPeriod / (365.25 * 86400);
            document.getElementById('body-period').textContent = years < 1 
                ? `${(years * 365.25).toFixed(1)} days` 
                : `${years.toFixed(2)} years`;
        } else {
            document.getElementById('body-period').textContent = '-';
        }
        
        // Focus camera on selected body
        this.scene.focusOn(body.position, 50);
    }

    createDefaultSolarSystem() {
        this.createSun();
        this.createPlanets();
        this.createOrbitLines();
    }

    /*--- Getters ---*/
    getSimulationTime() {
        return this.simulationTime;
    }

    getSimulationDays() {
        return this.simulationTime / 86400;
    }

    getSimulationYears() {
        return this.simulationTime / (365.25 * 86400);
    }
}