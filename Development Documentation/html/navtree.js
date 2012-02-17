var NAVTREE =
[
  [ "Trusted Transmission Tool", "index.html", [
    [ "T3 - Trusted Transmission Tool", "index.html", null ],
    [ "Class List", "annotated.html", [
      [ "ControllServer", "class_controll_server.html", null ],
      [ "Crypt", "class_crypt.html", null ],
      [ "Crypt3DES", "class_crypt3_d_e_s.html", null ],
      [ "CryptAES", "class_crypt_a_e_s.html", null ],
      [ "CryptBlowfish", "class_crypt_blowfish.html", null ],
      [ "CryptRSA", "class_crypt_r_s_a.html", null ],
      [ "ErrorLogger", "class_error_logger.html", null ],
      [ "ErrorPosition", "class_error_position.html", null ],
      [ "FileHandler", "class_file_handler.html", null ],
      [ "MainException", "class_main_exception.html", null ],
      [ "MainWindow", "class_main_window.html", null ],
      [ "ManagingFriendDialog", "class_managing_friend_dialog.html", null ],
      [ "PersonenList", "class_personen_list.html", null ],
      [ "RSAKeyPair", "class_r_s_a_key_pair.html", null ],
      [ "Settings", "class_settings.html", null ],
      [ "ShaApi", "class_sha_api.html", null ],
      [ "UserException", "class_user_exception.html", null ]
    ] ],
    [ "Class Index", "classes.html", null ],
    [ "Class Hierarchy", "hierarchy.html", [
      [ "ControllServer", "class_controll_server.html", null ],
      [ "Crypt", "class_crypt.html", [
        [ "Crypt3DES", "class_crypt3_d_e_s.html", null ],
        [ "CryptAES", "class_crypt_a_e_s.html", null ],
        [ "CryptBlowfish", "class_crypt_blowfish.html", null ],
        [ "CryptRSA", "class_crypt_r_s_a.html", null ]
      ] ],
      [ "ErrorLogger", "class_error_logger.html", null ],
      [ "ErrorPosition", "class_error_position.html", null ],
      [ "FileHandler", "class_file_handler.html", null ],
      [ "MainException", "class_main_exception.html", [
        [ "UserException", "class_user_exception.html", null ]
      ] ],
      [ "MainWindow", "class_main_window.html", null ],
      [ "ManagingFriendDialog", "class_managing_friend_dialog.html", null ],
      [ "PersonenList", "class_personen_list.html", null ],
      [ "RSAKeyPair", "class_r_s_a_key_pair.html", null ],
      [ "Settings", "class_settings.html", null ],
      [ "ShaApi", "class_sha_api.html", null ]
    ] ],
    [ "Class Members", "functions.html", null ],
    [ "Namespace List", "namespaces.html", [
      [ "Ui", "namespace_ui.html", null ]
    ] ],
    [ "File List", "files.html", [
      [ "Source/main.cpp", "main_8cpp.html", null ],
      [ "Source/Controller/controllserver.cpp", "controllserver_8cpp.html", null ],
      [ "Source/Controller/controllserver.h", "controllserver_8h.html", null ],
      [ "Source/Functions/crypt.cpp", "crypt_8cpp.html", null ],
      [ "Source/Functions/crypt.h", "crypt_8h.html", null ],
      [ "Source/Functions/crypt3des.cpp", "crypt3des_8cpp.html", null ],
      [ "Source/Functions/crypt3des.h", "crypt3des_8h.html", null ],
      [ "Source/Functions/cryptaes.cpp", "cryptaes_8cpp.html", null ],
      [ "Source/Functions/cryptaes.h", "cryptaes_8h.html", null ],
      [ "Source/Functions/cryptblowfish.cpp", "cryptblowfish_8cpp.html", null ],
      [ "Source/Functions/cryptblowfish.h", "cryptblowfish_8h.html", null ],
      [ "Source/Functions/cryptrsa.cpp", "cryptrsa_8cpp.html", null ],
      [ "Source/Functions/cryptrsa.h", "cryptrsa_8h.html", null ],
      [ "Source/Functions/sha_api.cpp", "sha__api_8cpp.html", null ],
      [ "Source/Functions/sha_api.h", "sha__api_8h.html", null ],
      [ "Source/Gui/mainwindow.cpp", "mainwindow_8cpp.html", null ],
      [ "Source/Gui/mainwindow.h", "mainwindow_8h.html", null ],
      [ "Source/Gui/managingfrienddialog.cpp", "managingfrienddialog_8cpp.html", null ],
      [ "Source/Gui/managingfrienddialog.h", "managingfrienddialog_8h.html", null ],
      [ "Source/Gui/settings.cpp", "settings_8cpp.html", null ],
      [ "Source/Gui/settings.h", "settings_8h.html", null ],
      [ "Source/Helper/errorlogger.cpp", "errorlogger_8cpp.html", null ],
      [ "Source/Helper/errorlogger.h", "errorlogger_8h.html", null ],
      [ "Source/Helper/errorposition.cpp", "errorposition_8cpp.html", null ],
      [ "Source/Helper/errorposition.h", "errorposition_8h.html", null ],
      [ "Source/Helper/filehandler.cpp", "filehandler_8cpp.html", null ],
      [ "Source/Helper/filehandler.h", "filehandler_8h.html", null ],
      [ "Source/Helper/globalDefines.h", "global_defines_8h.html", null ],
      [ "Source/Helper/mainexception.cpp", "mainexception_8cpp.html", null ],
      [ "Source/Helper/mainexception.h", "mainexception_8h.html", null ],
      [ "Source/Helper/userexception.cpp", "userexception_8cpp.html", null ],
      [ "Source/Helper/userexception.h", "userexception_8h.html", null ],
      [ "Source/Model/personenlist.cpp", "personenlist_8cpp.html", null ],
      [ "Source/Model/personenlist.h", "personenlist_8h.html", null ],
      [ "Source/Model/rsakeypair.cpp", "rsakeypair_8cpp.html", null ],
      [ "Source/Model/rsakeypair.h", "rsakeypair_8h.html", null ]
    ] ],
    [ "File Members", "globals.html", null ]
  ] ]
];

function createIndent(o,domNode,node,level)
{
  if (node.parentNode && node.parentNode.parentNode)
  {
    createIndent(o,domNode,node.parentNode,level+1);
  }
  var imgNode = document.createElement("img");
  if (level==0 && node.childrenData)
  {
    node.plus_img = imgNode;
    node.expandToggle = document.createElement("a");
    node.expandToggle.href = "javascript:void(0)";
    node.expandToggle.onclick = function() 
    {
      if (node.expanded) 
      {
        $(node.getChildrenUL()).slideUp("fast");
        if (node.isLast)
        {
          node.plus_img.src = node.relpath+"ftv2plastnode.png";
        }
        else
        {
          node.plus_img.src = node.relpath+"ftv2pnode.png";
        }
        node.expanded = false;
      } 
      else 
      {
        expandNode(o, node, false);
      }
    }
    node.expandToggle.appendChild(imgNode);
    domNode.appendChild(node.expandToggle);
  }
  else
  {
    domNode.appendChild(imgNode);
  }
  if (level==0)
  {
    if (node.isLast)
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2plastnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2lastnode.png";
        domNode.appendChild(imgNode);
      }
    }
    else
    {
      if (node.childrenData)
      {
        imgNode.src = node.relpath+"ftv2pnode.png";
      }
      else
      {
        imgNode.src = node.relpath+"ftv2node.png";
        domNode.appendChild(imgNode);
      }
    }
  }
  else
  {
    if (node.isLast)
    {
      imgNode.src = node.relpath+"ftv2blank.png";
    }
    else
    {
      imgNode.src = node.relpath+"ftv2vertline.png";
    }
  }
  imgNode.border = "0";
}

function newNode(o, po, text, link, childrenData, lastNode)
{
  var node = new Object();
  node.children = Array();
  node.childrenData = childrenData;
  node.depth = po.depth + 1;
  node.relpath = po.relpath;
  node.isLast = lastNode;

  node.li = document.createElement("li");
  po.getChildrenUL().appendChild(node.li);
  node.parentNode = po;

  node.itemDiv = document.createElement("div");
  node.itemDiv.className = "item";

  node.labelSpan = document.createElement("span");
  node.labelSpan.className = "label";

  createIndent(o,node.itemDiv,node,0);
  node.itemDiv.appendChild(node.labelSpan);
  node.li.appendChild(node.itemDiv);

  var a = document.createElement("a");
  node.labelSpan.appendChild(a);
  node.label = document.createTextNode(text);
  a.appendChild(node.label);
  if (link) 
  {
    a.href = node.relpath+link;
  } 
  else 
  {
    if (childrenData != null) 
    {
      a.className = "nolink";
      a.href = "javascript:void(0)";
      a.onclick = node.expandToggle.onclick;
      node.expanded = false;
    }
  }

  node.childrenUL = null;
  node.getChildrenUL = function() 
  {
    if (!node.childrenUL) 
    {
      node.childrenUL = document.createElement("ul");
      node.childrenUL.className = "children_ul";
      node.childrenUL.style.display = "none";
      node.li.appendChild(node.childrenUL);
    }
    return node.childrenUL;
  };

  return node;
}

function showRoot()
{
  var headerHeight = $("#top").height();
  var footerHeight = $("#nav-path").height();
  var windowHeight = $(window).height() - headerHeight - footerHeight;
  navtree.scrollTo('#selected',0,{offset:-windowHeight/2});
}

function expandNode(o, node, imm)
{
  if (node.childrenData && !node.expanded) 
  {
    if (!node.childrenVisited) 
    {
      getNode(o, node);
    }
    if (imm)
    {
      $(node.getChildrenUL()).show();
    } 
    else 
    {
      $(node.getChildrenUL()).slideDown("fast",showRoot);
    }
    if (node.isLast)
    {
      node.plus_img.src = node.relpath+"ftv2mlastnode.png";
    }
    else
    {
      node.plus_img.src = node.relpath+"ftv2mnode.png";
    }
    node.expanded = true;
  }
}

function getNode(o, po)
{
  po.childrenVisited = true;
  var l = po.childrenData.length-1;
  for (var i in po.childrenData) 
  {
    var nodeData = po.childrenData[i];
    po.children[i] = newNode(o, po, nodeData[0], nodeData[1], nodeData[2],
        i==l);
  }
}

function findNavTreePage(url, data)
{
  var nodes = data;
  var result = null;
  for (var i in nodes) 
  {
    var d = nodes[i];
    if (d[1] == url) 
    {
      return new Array(i);
    }
    else if (d[2] != null) // array of children
    {
      result = findNavTreePage(url, d[2]);
      if (result != null) 
      {
        return (new Array(i).concat(result));
      }
    }
  }
  return null;
}

function initNavTree(toroot,relpath)
{
  var o = new Object();
  o.toroot = toroot;
  o.node = new Object();
  o.node.li = document.getElementById("nav-tree-contents");
  o.node.childrenData = NAVTREE;
  o.node.children = new Array();
  o.node.childrenUL = document.createElement("ul");
  o.node.getChildrenUL = function() { return o.node.childrenUL; };
  o.node.li.appendChild(o.node.childrenUL);
  o.node.depth = 0;
  o.node.relpath = relpath;

  getNode(o, o.node);

  o.breadcrumbs = findNavTreePage(toroot, NAVTREE);
  if (o.breadcrumbs == null)
  {
    o.breadcrumbs = findNavTreePage("index.html",NAVTREE);
  }
  if (o.breadcrumbs != null && o.breadcrumbs.length>0)
  {
    var p = o.node;
    for (var i in o.breadcrumbs) 
    {
      var j = o.breadcrumbs[i];
      p = p.children[j];
      expandNode(o,p,true);
    }
    p.itemDiv.className = p.itemDiv.className + " selected";
    p.itemDiv.id = "selected";
    $(window).load(showRoot);
  }
}

