/**
 * File: node_group.cpp - Implementation of node group class,
 * part of Layout library in MiptVis tool.
 * Copyright (C) 2009  MIPTVIS
 */

#include "layout_iface.h" 
#include <QtCore/QtAlgorithms>

NodeGroup::NodeGroup(NodeAux* node)
{
	node_list.append(node);
	width_priv = node->width() + offset;
	pos = node->x();
	prev_priv = NULL;
	next_priv = NULL;
}

void NodeGroup::setNext(NodeGroup* group)
{
	next_priv = group;
};

void NodeGroup::setPrev(NodeGroup* group)
{
	prev_priv = group;
};

NodeGroup* NodeGroup::prev()
{
	return prev_priv;
}

NodeGroup* NodeGroup::next()
{
	return next_priv;
}

int NodeGroup::left()
{
	return pos - width_priv / 2;
};

int NodeGroup::right()
{
	return pos + width_priv / 2;
};

int NodeGroup::width()
{
	return width_priv;
}

void NodeGroup::median()
{
	QList<int> adj_pos; // Positions of andjacent to this group nodes
	for( QList<NodeAux*>::iterator v = node_list.begin(); v != node_list.end(); v++)
	{
		for( EdgeAux* iter = (*v)->firstSucc(); iter != NULL; iter = iter->nextSucc())
		{
			if(!iter->cycle())adj_pos.append(iter->succ()->x());
		}
		for( EdgeAux* iter = (*v)->firstPred(); iter != NULL; iter = iter->nextPred())
		{
			if(!iter->cycle())adj_pos.append(iter->pred()->x());
		}
	}
	qSort(adj_pos);
	/* Remove repeat elements */
	QList<int>::iterator prev = adj_pos.begin();
	for(QList<int>::iterator iter = ++adj_pos.begin(); iter < adj_pos.end();)
	{
		if(*iter == *prev)iter = adj_pos.erase(iter);
		else prev = iter++;
	}
	/* Calculate median position */
	int s = adj_pos.size();
	int m = s / 2;
	int ret = 0;
	if(s == 0) ret = pos;
	if(s == 1) ret = adj_pos[0];
	if(s == 2) ret = (adj_pos[0] + adj_pos[1]) / 2;
	if((s > 2) && (s % 2 == 1)) ret = adj_pos[m];
	if((s > 2) && (s % 2 == 0))
	{
		int l = adj_pos[m - 1] - adj_pos[0];
		int r = adj_pos[s - 1] - adj_pos[m];
		if(l + r)ret = (adj_pos[m - 1] * r + adj_pos[m] * l) / (l + r);
		else ret = 0;
	}
	pos = ret;
};

void NodeGroup::append()
{
	node_list.append(next()->node_list);
	if(next()->next() != NULL)next()->next()->setPrev(this);
	width_priv += next()->width();
	NodeGroup* next_tmp = next();
	setNext(next()->next());
	next_tmp->setNext(NULL);
	next_tmp->setPrev(NULL);
	next_tmp->node_list.clear();
	median();
	update();
};

void NodeGroup::prepend()
{
	prev()->append();
};

void NodeGroup::updatePos()
{
	int x = left() + offset / 2;
	for( QList<NodeAux*>::iterator iter = node_list.begin(); iter != node_list.end(); iter++)
	{
		(*iter)->msetX(x + (*iter)->width() / 2);
		x += offset + (*iter)->width();
	}
};

void NodeGroup::update()
{
	if(!empty())
	{
		updatePos();
		if(prev() != NULL) if(left() <= prev()->right()) prepend();
		if(next() != NULL) if(right() >= next()->left()) append();
	}
};

bool NodeGroup::empty()
{
	return node_list.isEmpty();
};