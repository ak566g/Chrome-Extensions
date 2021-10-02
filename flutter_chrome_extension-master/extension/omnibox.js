
let searchIndex = []
if (searchIndex.length == 0) {
  fetch('https://docs.flutter.io/flutter/index.json')
    .then((response) => response.json())
    .then((json) => {
      searchIndex = json;
    })
}

chrome.omnibox.onInputEntered.addListener((text) => {
  chrome.omnibox.
    console.log(text)
  var serviceCall2 = 'http://www.google.com/search?q=' + text;
  chrome.windows.create({ "url": serviceCall2 });
});

chrome.omnibox.onInputStarted.addListener(() => {

})

chrome.omnibox.onInputChanged.addListener((text, suggest) => {
  let results = searchIndex
    .filter((item) => item.qualifiedName.includes(text))
    .sort(compareType)
    .map((item) => generateEntry(text, item))
    .sort(compareName)
    .slice(0, 5)
  suggest(results);
})

let generateEntry = function (text, item) {
  let content = item.qualifiedName;
  let url = `https://docs.flutter.io/flutter/${item.href}`
  let name = highlight(item.name, text)
  let enclosed = item.enclosedBy ? highlight(item.enclosedBy.name, text) : ''
  let type = item.type.toLowerCase()
  let description = `${name} <dim>&lt;${type} ${enclosed}&gt;</dim>`;
  return { "content": content, "description": description }

}

let highlight = function (text, match) {
  if (text.includes(match)) {
    return text.replace(new RegExp("(" + match + ")", "gi"), "<match>$1</match>")
  } else {
    return text
  }
}

function compareType(a,b) {
  if (a.type < b.type)
    return -1;
  if (a.type > b.type)
    return 1;
  return 0;
}

function compareName(a,b) {
  if (a.name < b.name)
    return -1;
  if (a.name > b.name)
    return 1;
  return 0;
}
