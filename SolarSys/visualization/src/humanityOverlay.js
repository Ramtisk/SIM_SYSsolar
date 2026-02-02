export class HumanityOverlay {
    constructor(solarSystem) {
        this.solarSystem = solarSystem;
        
        /*--- Humanity state ---*/
        this.population = 8e9;
        this.homePlanet = 'Earth';
        this.colonies = [];
        this.techLevel = 1;
        
        /*--- Visual elements ---*/
        this.markers = [];
    }

    update(dt) {
        // Placeholder for humanity simulation
        // Will be expanded in future missions
    }

    addColonyMarker(planetName) {
        // Add visual marker for colonies
    }

    getPopulationString() {
        if (this.population >= 1e12) {
            return `${(this.population / 1e12).toFixed(2)} trillion`;
        } else if (this.population >= 1e9) {
            return `${(this.population / 1e9).toFixed(2)} billion`;
        } else if (this.population >= 1e6) {
            return `${(this.population / 1e6).toFixed(2)} million`;
        }
        return this.population.toLocaleString();
    }
}