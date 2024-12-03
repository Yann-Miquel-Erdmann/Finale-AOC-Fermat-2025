import os
documentation = \
"""<!DOCTYPE html>
<html style="--theme-color-1: rgb(92, 207, 230); --theme-color-2: rgb(255, 209, 115); --theme-color-3: rgb(115, 208, 255); --theme-color-4: rgb(213, 255, 128); --theme-color-5: rgb(149, 230, 203); --theme-color-6: rgb(242, 135, 121);">
  <head>
    <link rel="stylesheet" href="static/css/documentation.css">
    <link rel="stylesheet" href="static/css/colors.css">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.3/font/bootstrap-icons.min.css">
    <link rel="icon" sizes="96x96" href="static/favicon-96.png" type="image/png">
    <script src="static/js/color.js"></script>
    <script>
      function applyColors(){
        Array.from(document.getElementsByClassName("pre")).forEach((element) => {
          element.innerHTML = colorisation_doc(element.innerHTML);
        });
      }

      document.addEventListener("DOMContentLoaded", () => {
        Array.from(document.getElementsByClassName("bi-copy")).forEach((element) => {
        element.addEventListener("mousedown", () => {
          navigator.clipboard.writeText(element.parentElement.parentElement.firstElementChild.textContent);
          element.classList.add("bi-check2");
          element.classList.remove("bi-copy");
          setTimeout(() => {
            element.classList.add("bi-copy");
            element.classList.remove("bi-check2");
          }, 1000);
        });
      });
      })
      
      document.addEventListener("DOMContentLoaded", applyColors);
    </script>
  </head>
  <body>
    <div id="openDoc">
      <a href="" target="_blank">
        <i class="bi bi-box-arrow-up-right"></i>
      </a>
    </div>
    <div id="doclist">
"""

doclist = """
      <div id="DocSelection">
        <h4>Menu</h4>
"""
doctext = """
      <div id="docMain">
        <h2>Documentation</h2>
"""
nb_indent_doc = 4
nb_indent = 4

in_p = False
with open("Documentation.md") as file:
    code = False
    for i, line in enumerate(file.readlines()[2:]):
        line = line.replace("...", "&#8230;")
        line = line.replace("<", "&lt;")
        line = line.replace(">", "&gt;")
        modif = False
        title = False
        if line == "```\n":
            if code:
                doctext = doctext[:-1]
                doctext += "</div>\n"
                doctext += "  "*(nb_indent+1)+'<div class="copy-container">\n' + "  "*(nb_indent+2)+'<i class="bi bi-copy"></i>\n' + "  "*(nb_indent+1)+'</div>\n' + "  "*nb_indent+'</div>'
            else:
                doctext += "  "*nb_indent + '<div class="pre-container">\n'
                doctext += "  "*(nb_indent+1)+'<div class="pre">'
            code = not code
        else:
            if code:
                doctext += line
            if not code:
                if line[0:2] == "##":
                    id = line[3:].replace(" ", "_").lower().strip()
                    title = line[3:].strip()
                    doclist += \
                        nb_indent_doc*'  ' + f'<div class="selectContainer">\n' + \
                        nb_indent_doc*'  ' + f'  <a href="#{id}">{title}</a>\n' + \
                        nb_indent_doc*'  ' + f'</div>\n'
                    if in_p:
                        nb_indent -= 1
                        doctext += nb_indent * '  ' + '</div>\n'
                    doctext += \
                        nb_indent * '  ' + f'<h3 id="{id}">{title}</h3>\n' +\
                        nb_indent * '  ' + '<div>\n'
                    nb_indent += 1
                    in_p = True
                if "**" in line:
                    while "**" in line:
                        b = line.index("**")+2
                        e = line.index("**", b+1)
                        line = f"{line[0:b-2]}<b>{line[b:e]}</b>{line[e+2:]}"
                if line[0] == "*":
                    line = f"<b>•</b> {line[2:]}"
                if "`" in line:
                    while "`" in line:
                        b = line.index("`") + 1
                        e = line.index("`", b+1)
                        line = f'{line[0:b-1]}"<i class="code">{line[b:e]}</i>"{line[e+1:]}'
                if "_" in line:
                    while "_" in line:
                        b = line.index("_") + 1
                        e = line.index("_", b + 1)
                        line = f"{line[0:b - 1]}<i>{line[b:e]}</i>{line[e + 1:]}"

                if not title:
                    doctext += "  "*nb_indent + line.replace("\n", "<br>\n")
    nb_indent_doc -= 1
    doclist += nb_indent_doc * '  ' + "</div>"
    nb_indent -= 1
    doctext += nb_indent*'  '+"</p>\n"
    doctext += (nb_indent-1)*'  ' + "</div>"
documentation += doclist + doctext + "\n    </div>\n  <body>\n<html>"
with open("build/documentation.html", 'w+') as file:
    file.write(documentation)
