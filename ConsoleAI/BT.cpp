#include "pch.h"
#include "BT.h"

BT_NODE::BTRoot* const		BT::Root() { return new BT_NODE::BTRoot(); }
BT_NODE::BTSequence* const	BT::Sequence() { return new BT_NODE::BTSequence(); }
BT_NODE::BTSelector* const	BT::Selector() { return new BT_NODE::BTSelector(); }
BT_NODE::BTAction* const	BT::Action(const BT_NODE::BTAction::FP& fp) { return new BT_NODE::BTAction(fp); }
BT_NODE::BTCondition* const	BT::Condition(const BT_NODE::BTCondition::FP& fp) { return new BT_NODE::BTCondition(fp); }
BT_NODE::BTSwitch* const	BT::Switch(BT_NODE::BTNode* child) { return new BT_NODE::BTSwitch(child); }
