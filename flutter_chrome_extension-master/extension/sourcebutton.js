
let getFilename = function () {
  return document.URL.split('#').shift().split('?').shift().split('/').pop().replace(".html", "");
}

let filename = getFilename();
let [name, type] = filename.split("-")

if (type && type.toLowerCase() === "class") {
  let title = document.getElementsByTagName("h1")[0];

  let typeUrls = urls[type]
  if (urls[type] && urls[type][name]) {
    url = urls[type]["base"] + urls[type][name];
    title.outerHTML = `<a href="${url}" target="_blank" class="flce-source-link">See source code for ${name} ${type}</a>` + title.outerHTML
  }
}
