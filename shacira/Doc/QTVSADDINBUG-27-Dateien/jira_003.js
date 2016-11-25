jQuery.fn.stalker=function(){var $win=jQuery(window),$doc=jQuery(document),$stalkerContent,$stalker,$transitionElems,offsetY,placeholder,lastScrollPosY,stalkerHeight,selector=this.selector;function getScrollTop(scrollPos){return Math.max(0,jQuery(window).scrollTop(scrollPos))}function supportsOpacityTransition(){return !jQuery.browser.msie||(jQuery.browser.msie&&jQuery.browser.version>8)}function getInactiveProperties(){return{position:"fixed",top:offsetY-getScrollTop()}}function initialize(){$stalker=jQuery(selector);if($stalker.length===0||$stalker.data("stalkerIntialized")){return }$stalker.data("stalkerIntialized",true);$doc.bind("keydown",function(event){if(AJS.consumesKeyboardEvents(jQuery(event.target))){return }var handler;switch(event.keyCode){case AJS.$.ui.keyCode.SPACE:handler=(event.shiftKey)?pageUp:pageDown;break;case AJS.$.ui.keyCode.PAGE_UP:handler=pageUp;break;case AJS.$.ui.keyCode.PAGE_DOWN:handler=pageDown;break;default:return }if(jQuery("body").css("overflow")!=="hidden"){handler()}event.preventDefault()});offsetY=$stalker.offset().top;$stalkerContent=$stalker.find(".issue-header-content");$transitionElems=AJS.$("#header");function setStalkerHeight(){$stalker.css("overflow","hidden");stalkerHeight=$stalker.outerHeight();$stalker.css("overflow","")}function createPlaceholder(){placeholder=jQuery("<div />").addClass("stalker-placeholder").css({visibility:"hidden",height:stalkerHeight}).insertBefore($stalker)}function setPlaceholderHeight(){placeholder.height($stalkerContent.outerHeight())}setStalkerHeight();createPlaceholder();setPlaceholderHeight();$stalker.css(getInactiveProperties());$stalker.bind("stalkerHeightUpdated",setPlaceholderHeight);$stalker.bind("positionChanged",setStalkerPosition)}function setScrollPostion(scrollTarget){var docHeight=jQuery.getDocHeight(),scrollPos;if(scrollTarget>=0&&scrollTarget<=docHeight){scrollPos=scrollTarget}else{if(scrollTarget>=getScrollTop()){scrollPos=docHeight}else{if(scrollTarget<0){scrollPos=0}}}getScrollTop(scrollPos)}function pageUp(){initialize();var scrollTarget=getScrollTop()-jQuery(window).height();setScrollPostion(scrollTarget+stalkerHeight)}function pageDown(){initialize();var scrollTarget=getScrollTop()+jQuery(window).height();setScrollPostion(scrollTarget-stalkerHeight)}function containDropdownsInWindow(){$doc.bind("showLayer",function(e,type,obj){var stalkerOffset,targetHeight;initialize();if(type==="dropdown"&&obj.$.parents(selector).length!==-1){stalkerOffset=($stalker.hasClass("detached")||!$stalker.offset()?0:$stalker.offset().top);targetHeight=jQuery(window).height()-$stalker.height()-stalkerOffset;if(targetHeight<=parseInt(obj.$.attr("scrollHeight"),10)){JIRA.containDropdown.containHeight(obj,targetHeight)}else{JIRA.containDropdown.releaseContainment(obj)}obj.reset()}})}if(jQuery.browser.msie){jQuery(setup);jQuery(setStalkerPosition)}else{setup()}function setup(){containDropdownsInWindow();$doc.click(function(e){if(jQuery(e.target).parents(selector).length!==0){initialize()}});$doc.bind("showLayer",function(e,type,obj){if(obj&&$transitionElems&&supportsOpacityTransition()){var $offsetTarget=obj.$offsetTarget||obj.trigger;if($offsetTarget&&$offsetTarget[0]){for(var i=0;i<$transitionElems.length;i++){if($transitionElems[i]===$offsetTarget[0]||jQuery.contains($transitionElems[i],$offsetTarget[0])){$transitionElems.css("opacity","");break}}}else{if(obj.id==="create_issue_popup"){$transitionElems.css("opacity","")}}}if(jQuery.browser.mozilla&&type==="popup"){setStalkerPosition()}});$win.scroll(setStalkerPosition);$win.resize(function(){if($stalker){$stalker.trigger("stalkerHeightUpdated")}})}function setStalkerPosition(){function getOpacitySetting(){var opacityTarget=1-getScrollTop()/offsetY;if(opacityTarget>1){return""}else{if(opacityTarget<0){return 0}else{return opacityTarget}}}initialize();if(supportsOpacityTransition()&&$transitionElems){$transitionElems.css("opacity",getOpacitySetting())}if(offsetY<=getScrollTop()){if(!$stalker.hasClass("detached")){$stalker.css({top:0,position:"fixed"}).addClass("detached")}}else{$stalker.css(getInactiveProperties()).removeClass("detached")}lastScrollPosY=getScrollTop()}return this};
JIRA.OffsetAnchors=Class.extend({WEBKIT_SCROLL_DELAY:100,BUFFER:20,init:function(offsetElemSelector){this.offsetElemSelector=offsetElemSelector;this.listen()},offsetElement:function(){if(!this.$offsetElement){this.$offsetElement=AJS.$(this.offsetElemSelector)}return this.$offsetElement},targetElement:function(){var anchor=this.anchor();if(anchor){var escapedAnchor=AJS.escapeHtml(anchor);var targetElement;try{targetElement=AJS.$("#"+escapedAnchor+",a[name="+escapedAnchor+"]").filter(":visible")}catch(e){return null}if(targetElement.length!==0){return targetElement.eq(0)}}},_bottomOfOffsetElement:function(){return this.offsetElement().outerHeight()+this.offsetElement().offset().top},offsettedScrollPosition:function(targetElement){return targetElement.offset().top-this.BUFFER-this.offsetElement().outerHeight()},offset:function(){var targetElement,scrollPosition;targetElement=this.targetElement();this.scrolled=true;if(targetElement){scrollPosition=this.offsettedScrollPosition(targetElement);if(AJS.$.browser.safari){this._delayScrollForWebkit(scrollPosition)}else{AJS.$(window).scrollTop(scrollPosition)}}},_delayScrollForWebkit:function(scrollTarget){window.setTimeout(function(){AJS.$(window).scrollTop(scrollTarget)},this.WEBKIT_SCROLL_DELAY)},anchor:function(){return parseUri(window.location.href).anchor},listen:function(){var instance=this;AJS.$(window).one("scroll",function(){if(!instance.scrolled){instance.offset()}})}});
JIRA.ViewIssueTabs=(function(){var AJAX_LOAD_CLASS="ajax-activity-content";var AJAX_LINK_SELECTOR=AJS.format("a.{0}",AJAX_LOAD_CLASS);var issueTabLoadedListeners=[];var $tabContents,$tabProgress;var xhrInProgress;function dispatchIssueTabLoadedEvent(container){AJS.$.each(issueTabLoadedListeners,function(i,fn){fn(container)})}function bindToTabDivs(container){$tabContents=AJS.$(container).find("#issue_actions_container");$tabProgress=AJS.$(container).find("div.issuePanelProgress")}function dispatchIssueTabErrorEvent(smartAjaxResult,activeTabKey){var errorPopup=new JIRA.FormDialog({id:"issue-tab-error-dialog",widthClass:"small",content:JIRA.SmartAjax.buildDialogErrorContent(smartAjaxResult,false)});setActiveTab(activeTabKey);$tabContents.show();errorPopup.show()}function setActiveTab(activeTabKey){AJS.$("#issue-tabs li").each(function(){var $li=AJS.$(this);var tabKey=$li.data("key");var labelHtml=AJS.format("<strong>{0}</strong>",$li.data("label"));if(tabKey==activeTabKey){$li.addClass("active");$li.html(labelHtml)}else{$li.removeClass("active");var id=$li.data("id");var href=$li.data("href");$li.html(AJS.format('<a id="{0}" href="{1}" class="{2}">{3}</a>',id,href,AJAX_LOAD_CLASS,labelHtml))}});enablePjaxOnLinks(AJS.$("#issue-tabs"))}function putTabInLoadingState(activeTabKey){$tabContents.hide();setActiveTab(activeTabKey)}function enablePjaxOnLinks(context){var activeTabKey=AJS.$(context).find("li.active").data("key");AJS.$(context).find(AJAX_LINK_SELECTOR).click(function(event){if(event.metaKey){return }event.preventDefault();if(xhrInProgress){xhrInProgress.abort()}var $a=AJS.$(this);var containerID="#activitymodule div.mod-content";var loadingTabKey=$a.parent().data("key");putTabInLoadingState(loadingTabKey);var xhr=JIRA.SmartAjax.makeRequest({jqueryAjaxFn:AJS.$.pjax,container:containerID,url:$a.attr("href"),timeout:null,complete:function(xhr,status,smartAjaxResult){if(status!="abort"){xhrInProgress=null;if(!smartAjaxResult.successful){if(smartAjaxResult.status<300||smartAjaxResult.status>=400){dispatchIssueTabErrorEvent(smartAjaxResult,activeTabKey)}return }dispatchIssueTabLoadedEvent(AJS.$(containerID))}}});jQuery(xhr).throbber({target:$tabProgress});xhrInProgress=xhr})}function appendHashCodeToLinks(context){AJS.$(context).find(AJAX_LINK_SELECTOR).each(function(){var $a=AJS.$(this);$a.attr("href",$a.attr("href")+"#issue-tabs")})}function processActivityModuleLinks(context){if(AJS.$.support.pjax){enablePjaxOnLinks(context)}else{appendHashCodeToLinks(context)}}return{onTabReady:function(listener){issueTabLoadedListeners.push(listener)},domReady:function(){this.onTabReady(bindToTabDivs);this.onTabReady(processActivityModuleLinks);dispatchIssueTabLoadedEvent(document)}}})();
JIRA.ViewIssue=(function(){function setFocusConfiguration(){if(parseUri(window.location.href).anchor!=="summary"){var triggerConfig=new JIRA.setFocus.FocusConfiguration();triggerConfig.excludeParentSelector="#"+FORM_ID+",.dont-default-focus";JIRA.setFocus.pushConfiguration(triggerConfig)}else{AJS.$("#summary").focus()}}function listenForEvents(){var subtaskTrigger;JIRA.bind("QuickCreateSubtask.sessionComplete",function(e,issues){JIRA.Issue.getSubtaskModule().addClass("updating");JIRA.Issue.refreshSubtasks().done(function(){subtaskTrigger=document.getElementById("stqc_show");if(subtaskTrigger){subtaskTrigger.onclick=null}JIRA.Issue.highlightSubtasks(issues);JIRA.Issue.getSubtaskModule().removeClass("updating")})});JIRA.bind("QuickEdit.sessionComplete",function(){JIRA.Issue.reload()})}var FORM_ID="stqcform";var subtasks={domReady:function(){setFocusConfiguration()}};var stalker={init:function(){new JIRA.OffsetAnchors("#stalker.js-stalker, .stalker-placeholder")}};function setupMouseoverBehaviour(context){if(jQuery.browser.msie&&parseInt(jQuery.browser.version,10)===7){jQuery("a.twixi").bind("focus",function(e){e.preventDefault()})}else{jQuery(document).bind("moveToFinished",function(event,target){jQuery("a.twixi:visible",target).focus()})}}var issueTabs={domReady:function(){JIRA.ViewIssueTabs.onTabReady(setupMouseoverBehaviour);JIRA.ViewIssueTabs.onTabReady(JIRA.userhover);JIRA.ViewIssueTabs.domReady()}};return{init:function(){stalker.init()},domReady:function(){subtasks.domReady();issueTabs.domReady();listenForEvents()}}})();JIRA.ViewIssue.init();AJS.$(JIRA.ViewIssue.domReady);AJS.namespace("jira.app.viewissue",null,JIRA.ViewIssue);jQuery(function(){var openInNewWindow=function(e){e.preventDefault();e.stopPropagation();var $this=jQuery(this);jQuery(document).click();new JIRA.ScreenshotDialog({trigger:$this}).openWindow()};AJS.$("#attach-screenshot").click(openInNewWindow);var toggleVotingAndWatching=function(trigger,className,resultContainer,issueOpTrigger,i18n){var classNameOn=className+"-on",classNameOff=className+"-off",icon=trigger.find(".icon"),restPath="/voters",data,method="POST";if(icon.hasClass(classNameOn)){method="DELETE"}if(className.indexOf("watch")!==-1){restPath="/watchers"}icon.removeClass(classNameOn).removeClass(classNameOff);if(method==="POST"){data={dummy:true}}AJS.$(JIRA.SmartAjax.makeRequest({url:contextPath+"/rest/api/1.0/issues/"+trigger.attr("rel")+restPath,type:method,dataType:"json",data:data,contentType:"application/json",complete:function(xhr,textStatus,smartAjaxResult){if(smartAjaxResult.successful){if(method==="POST"){icon.addClass(classNameOn);trigger.attr("title",i18n.titleOn).find(".action-text").text(i18n.actionTextOn);issueOpTrigger.attr("title",i18n.titleOn).text(i18n.textOn)}else{icon.addClass(classNameOff);trigger.attr("title",i18n.titleOff).find(".action-text").text(i18n.actionTextOff);issueOpTrigger.attr("title",i18n.titleOff).text(i18n.textOff)}resultContainer.text(smartAjaxResult.data.count)}else{alert(JIRA.SmartAjax.buildSimpleErrorContent(smartAjaxResult,{alert:true}));if(method==="POST"){icon.addClass(classNameOff);trigger.attr("title",i18n.titleOff).find(".action-text").text(i18n.actionTextOff);issueOpTrigger.attr("title",i18n.titleOff).text(i18n.textOff)}else{icon.addClass(classNameOn);trigger.attr("title",i18n.titleOn).find(".action-text").text(i18n.actionTextOn);issueOpTrigger.attr("title",i18n.titleOn).text(i18n.textOn)}}}})).throbber({target:icon})};function toggleWatch(){AJS.$("#watching-toggle").click()}AJS.$("#toggle-vote-issue").click(function(e){e.preventDefault();AJS.$("#vote-toggle").click()});AJS.$("#toggle-watch-issue").click(function(e){e.preventDefault();toggleWatch()});var addI18nErrorCodes=function(i18n){AJS.$("input[type=hidden][id|=error]").each(function(index,elem){var i18n_id=elem.id.replace("error-","");i18n[i18n_id]=elem.value})};AJS.$("#vote-toggle").click(function(e){e.preventDefault();var i18n={titleOn:"Remove vote for this issue",titleOff:"Vote for this issue",textOn:"Remove Vote",textOff:"Add Vote",actionTextOff:"Vote",actionTextOn:"Voted"};addI18nErrorCodes(i18n);toggleVotingAndWatching(AJS.$(this),"icon-vote",AJS.$("#vote-data"),AJS.$("#toggle-vote-issue"),i18n)});AJS.$("#watching-toggle").click(function(e){e.preventDefault();var i18n={titleOn:"Stop watching this issue",titleOff:"Start watching this issue",textOn:"Stop Watching",textOff:"Watch Issue",actionTextOff:"Watch",actionTextOn:"Watching"};addI18nErrorCodes(i18n);toggleVotingAndWatching(AJS.$(this),"icon-watch",AJS.$("#watcher-data"),AJS.$("#toggle-watch-issue"),i18n)});AJS.moveInProgress=false;AJS.$(document).bind("moveToStarted",function(){AJS.moveInProgress=true}).bind("moveToFinished",function(){AJS.moveInProgress=false});if(parseUri(window.location.href).anchor==="add-comment"){AJS.$("#footer-comment-button").click()}});
