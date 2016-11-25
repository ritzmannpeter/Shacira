
#include <qdom.h>
#include <qfile.h>
#include <stdio.h>
#include "cgraph.h"

static STRING_T StripText(const char * text)
{
   STRING_T stripped_text;
   int len = strlen(text);
   int i = 0;
   for (i=1; i<len-1; i++) {
      stripped_text += text[i - 1];
   }
   return stripped_text;
}

bool ParseProperties(cGraph * graph, cAngle * parent_angle,
                     QDomElement * element, int level = 0)
{
   QDomNodeList children = element->childNodes();
   int child_count = children.count();
   QDomElement current_element;
   int i = 0;
   for (i=0; i<child_count; i++) {
      current_element = children.item(i).toElement();
      QString text = current_element.text();
      QString tag_name = current_element.tagName();
      if (tag_name == "property") {
         QString property_name;
         if (current_element.hasAttribute("name")) {
			   property_name = current_element.attribute("name");
         } else {
            return false;
         }
         STRING_T value = StripText(text);
         parent_angle->AddProperty(property_name, value.c_str());
         return true;
      } else {
         /// angles only have properties
         /// no further angles no nodes
         return false;
      }
   }
   return true;
}

bool ParseElements(cGraph * graph, cNode * parent_node,
                   QDomElement * element, int level = 0)
{
   QDomNodeList children = element->childNodes();
   int child_count = children.count();
   QDomElement current_element;
   int i = 0;
   for (i=0; i<child_count; i++) {
      current_element = children.item(i).toElement();
      QString text = current_element.text();
      QString tag_name = current_element.tagName();
      if (tag_name == "property") {
         QString property_name;
         if (current_element.hasAttribute("name")) {
			   property_name = current_element.attribute("name");
         } else {
            return false;
         }
         STRING_T value = StripText(text);
         if (parent_node != NULL) {
            parent_node->AddProperty(property_name, value.c_str());
         } else {
            return false;
         }
      } else if (tag_name == "node") {
         if (current_element.hasAttribute("name")) {
            QString node_name = current_element.attribute("name");
            cNode * node = graph->Node(node_name);
            ParseElements(graph, node, &current_element, level + 1);
         } else {
            return false;
         }
      } else if (tag_name == "angle") {
         QString angle_name;
         QString source_name;
         QString target_name;
         if (current_element.hasAttribute("name")) {
            angle_name = current_element.attribute("name");
         } else {
            return false;
         }
         if (current_element.hasAttribute("source")) {
            source_name = current_element.attribute("source");
         } else {
            return false;
         }
         if (current_element.hasAttribute("target")) {
            target_name = current_element.attribute("target");
         } else {
            return false;
         }
         cNode * source_node = graph->Node(source_name);
         cNode * target_node = graph->Node(target_name);
         cAngle * angle = new cAngle(graph, angle_name, source_node, target_node);
         if (parent_node != NULL) {
            ParseProperties(graph, angle, &current_element, level + 1);
            parent_node->AddAngle(angle);
            ParseElements(graph, target_node, &current_element, level + 1);
         } else {
            return false;
         }
      }
   }
   return true;
}

bool ParseGraph(cGraph * graph, const char * xml_file)
{
   bool success = false;
   int err_line = 0;
   int err_column = 0;
   QFile qfile(xml_file);
   if (qfile.open(IO_ReadOnly)) {
      QString err_msg;
      QDomDocument * document = new QDomDocument();
      if (document->setContent(&qfile, &err_msg, &err_line, &err_column)) {
         QDomElement element = document->documentElement();
         success = ParseElements(graph, NULL, &element);
      }
      qfile.close();
   }
   return success;
}

#define TEST_IT
#ifdef TEST_IT

int main(int argc, char* argv[])
{
   const char * file = "test.xml";
   if (argc == 2) {
      file = argv[1];
   }
   char h_file[0x200] = {0};
   char f_file[0x200] = {0};
   sprintf(h_file, "%s.hier", file);
   sprintf(f_file, "%s.flat", file);
   cGraph * graph = new cGraph;
   printf("parsing %s ...\n", file);
   if (ParseGraph(graph, file)) {
      STRING_T xml_data;
      cNode * node = graph->Node("root");
      graph->SetRootNode(node);
      graph->ResetFlag(HIERARCHICAL_XML_OUTPUT);
      graph->XML(xml_data);
      remove(f_file);
      FILE * stream = fopen(f_file, "a");
      if (stream != NULL) {
         fprintf(stream, "%s", xml_data.c_str());
         fclose(stream);
      }
      xml_data = "";
      graph->SetFlag(HIERARCHICAL_XML_OUTPUT);
      graph->XML(xml_data);
      remove(h_file);
      stream = fopen(h_file, "a");
      if (stream != NULL) {
         fprintf(stream, "%s", xml_data.c_str());
         fclose(stream);
      }
      printf("done %s\n", file);
      return 0;
   } else {
      printf("failed to parse %s\n", file);
      return -1;
   }
}

#endif
