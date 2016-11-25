
#ifndef _cGraph_h
#define _cGraph_h 	1

#include "global_defs.h"
#include "cnode.h"
#include "cangle.h"

#define HIERARCHICAL_XML_OUTPUT  0x00000001     ///> XML output reflects hierarchies when present
                                                ///> if not set a flat output is generated

/**
  * @brief Represents a graph
  * a graph has a set of nodes and a set of angles to connect arbitrary nodes of the graph
  * 
  */
class cGraph {
public:
   cGraph();
   virtual ~cGraph();
   /**
     * @brief Returns the root node of a graph
     * The root node of a graph is a node that must be marked using SetRootNode.
     * As a consequence a graph must not have a root node. In this case the method
     * will return NULL.
     */	
   inline cNode * RootNode()
   {
      return _RootNode;
   };
   /**
     * @brief This method sets the root node of a graph.
     * If a root node already exists this root node will be reset (is no longer root node).
     * @param node A pointer to the node that will be marked as root node
     */	
   inline void SetRootNode(cNode * node)
   {
      _RootNode = node;
   };
   /**
     * @brief This method returns the flags associated with a graph.
     */	
   inline unsigned long cGraph::Flags()
   {
      return _Flags;
   };
   /**
     * @brief This method sets all flags of a graph to the supplied value
     * @param flags the new flags for the graph
     */	
   inline void cGraph::SetFlags(unsigned long flags)
   {
      _Flags = flags;
   };
   /**
     * @brief This method sets all graph flags masked by flag
     * @param flag mask of the flags to be set
     */	
   inline void cGraph::SetFlag(unsigned long flag)
   {
      _Flags |= flag;
   };
   /**
     * @brief This method resets all graph flags masked by flag
     * @param flag mask of the flags to be reset
     */	
   inline void cGraph::ResetFlag(unsigned long flag)
   {
      _Flags &= (~flag);
   };
   /**
     * @brief Factory method for cNode objects
     * This method retrieves a node with the specified name or creates a new one.
     * @param name Name of the node to be created or retrieved.
     * Node names are unambigious within a graph. Two nodes with the same name
     * are identical objects (they have the same memory address),
     */	
   cNode * Node(const char * name);
   /**
     * @brief Method to pretty print the graph into a file.
     * @param stream FILE pointer for the file to print into
     */	
   virtual void Print(FILE * stream, int level = 0);
   /**
     * @brief Method to generate an XML representation of the graph
     * @param text string reference to hold xml data
     * @param level used for identation
     */	
   virtual void XML(STRING_T & text, int level = 0);
private:
   void AddNode(cNode * node);
   void AddAngle(cAngle * angle);
protected:
   unsigned long _Flags;
   cNode * _RootNode;
   NODE_VECTOR_T _Nodes;
   ANGLE_VECTOR_T _Angles;
   GRAPH_NODE_MAP_T _NodeMap;
};

#endif

