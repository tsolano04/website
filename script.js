CROSSWORD_GRID_SIZE = 15

class Website {
    constructor()
    {
        this.crosswordGridSize = CROSSWORD_GRID_SIZE;
        this.init();
    }

    async init () {
        this.pages = await this.getPages();
        console.log('Pages loaded:', this.pages);
        
        this.crosswordGrid = new CrosswordGrid(this.crosswordGridSize, this.pages);
        console.log('Crossword grid initialized:', this.crosswordGrid);

    }

    

    mapCrosswordToSite(){
        
    }
}

module.exports = { Website };
