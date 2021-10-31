class Thing {
    constructor({ node, score = 0, scoreRating = 0, comments = 0, commentsRating = 0 }) {
        this.node = node;
        this.score = score;
        this.scoreRating = scoreRating;
        this.comments = comments;
        this.commentsRating = commentsRating;
    }
}

class Boundaries {
    constructor() {
        this.score = { min: Number.MAX_VALUE, max: 0 };
        this.comments = { min: Number.MAX_VALUE, max: 0 };
    }
    calculate (value, type) {
        if (value > this[type].max) this[type].max = value;
        if (value < this[type].min) this[type].min = value;
    }
    calcScore (value) {
        this.calculate(value, 'score');
    }
    calcComments (value) {
        this.calculate(value, 'comments');
    }
}

const getScore = (thingNode) => {
    const node = thingNode.nextElementSibling.querySelector('.score');
    return node != null ? parseFloat(node.innerText) : 0;
}

const getComments = (thingNode) => {
    const node = thingNode.nextElementSibling.querySelector('[href^="item"]');
    return node != null ? parseFloat(node.innerText) : 0;
}

const rate = (value, min, max) => {
    return Math.round(5 * (value - min) / (max - min));
}

const prepareMap = () => {
    const things = [];
    const boundaries = new Boundaries();

    document.querySelectorAll('.athing').forEach(thingNode => {
        const score = getScore(thingNode);
        const comments = getComments(thingNode);
        boundaries.calcScore(score);
        boundaries.calcComments(comments);
        things.push(new Thing({
            node: thingNode.nextElementSibling.querySelector('.subtext'),
            score,
            comments,
        }));
    });

    things.forEach(thing => {
        thing.scoreRating = rate(thing.score, boundaries.score.min, boundaries.score.max);
        thing.commentsRating = rate(thing.comments, boundaries.comments.min, boundaries.comments.max);
    });

    return things;
}

const getStars = (value) => {
    const filled = '★';
    const empty = '☆';
    return filled.repeat(value) + empty.repeat(5 - value);
}

prepareMap().forEach(thing => {
    const span = document.createElement('span');
    span.setAttribute('style', 'color: crimson; font-size: 1.2em;');
    span.innerText = `Score: ${getStars(thing.scoreRating)}, Comments: ${getStars(thing.commentsRating)}`;
    thing.node.prepend(span);
});
