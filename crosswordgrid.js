class CrosswordGrid {
    constructor(size, words)
    {
        this.size = size;
        this.words = words.map(w => new Word(w.toLowerCase()));
        this.grid = this.createGrid();
        this.wordObjects = [];
        this.placeWords();
    }
    
    createGrid() {
        const grid = [];
        for (let i = 0; i < this.size; i++) {
            const row = new Array(this.size).fill('');
            grid.push(row);
        }
        return grid;
    }

    placeWords() {
        this.placeFirstWord(this.words[0]);
        console.log('Placing words in the crossword grid:', this.words);
        for (let i = 0; i < this.words.length; i++)
        {
            const currentWord = this.words[i]
            this.placeWord(currentWord);
        }
    }

    placeFirstWord(word) {
        const midpoint = Math.floor(this.size/2);
        const wordLength = word.length
        const difference = this.size - wordLength;
        const start = Math.floor(difference/2);
        if (word.length > this.size){
            console.log("Can't place word, too big for grid");
            return;
        }
        for (let i = 0; i < wordLength; i++){
            let currentLetter = word.letters[i];
            this.grid[midpoint][start + i] = currentLetter.letter.toUpperCase();
            currentLetter.assignCoordinates(midpoint, start + i);
        }
        word.orientation = 'across';
        this.addNewWord(word);
        this.removeWordFromList(0);
    }

    placeWord(word) {
        const self = this;

        for (let i = 0; i < word.length; i++){
        const currentLetter = word.letters[i];
            for (let j = 0; j < self.wordObjects.length; j++){
                const gridWord = self.wordObjects[j];
                if(intersectionFound(currentLetter, gridWord)){
                    console.log("Found match: " + word.word + ' '+ currentLetter.letter)
                }
            }
        }

        console.log(word);

        function intersectionFound(letter, word){
            let currentLetter = letter.letter;
            const currentWord = word.word;
            
            for(let i = 0; i < word.length; i++){
                const wordLetter = currentWord[i];
                if (wordLetter == currentLetter){
                    letter = word.letters[i];
                    console.log(letter);
                    console.log(word.letters[i]);
                    return true;
                }
            }
            return false;
        }

        function canPlace(){

        }
    }

    addNewWord(word){
        this.wordObjects.push(word);
    }

    removeWordFromList(index) {
        this.words.splice(index, 1);
    }
}

class Word {
    constructor(word, orientation = 'None') {
        this.word = word;
        this.orientation = orientation;
        this.intersectionIndex;
        this.letters = [];
        this.length = this.word.length;
        this.init();
    }
    
    init(){
        for (let i = 0; i < this.word.length; i++){
            this.letters.push(new Letter(i, this.word[i]));
        }
    }

    opposite(){
        if(this.orientation == 'across'){
            return 'down';
        } 
        else if (this.orientation == 'down'){
            return 'across';
        }
    }
}

class Letter {
    constructor(index, letter){
        this.index = index;
        this.letter = letter;
        this.xCord = null;
        this.yCord = null;
    }

    assignCoordinates(x, y) {
        this.xCord = x;
        this.yCord = y;
    }

    resetCoordinates() {
        this.xCord = null;
        this.yCord = null;
    }
}

module.exports = { CrosswordGrid, Word, Letter};