#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

#define OPEN_NAMESPACE(x)	namespace x {
#define CLOSE_NAMESPACE(x)	}

enum class eBT
{
	Fail,
	Success,
	Continue,
	Abort,
};

OPEN_NAMESPACE(BT_NODE)

// 최상위 클래스
struct BTNode
{
	virtual ~BTNode() {}

	virtual eBT Tick() = 0;
};

struct BTNode;
using NodeList = std::vector<struct BTNode*>;

// Tick() 은 일부러 재정의 안함. 자식을 여럿 가지는 추상 클래스
struct BTList : BTNode
{
	virtual ~BTList()
	{
		for (auto* pNode : children)
		{
			delete pNode;
			pNode = nullptr;
		}

		children.clear();
	}

	virtual BTList* Add(std::initializer_list<BTNode*> list)
	{
		for (auto* p : list)
		{
			children.push_back(p);
		}

		return this;
	}

	virtual BTList* Add2(std::vector<BTNode*> list)
	{
		for (auto* p : list)
		{
			children.push_back(p);
		}

		return this;
	}

	NodeList& GetChildren()
	{
		return children;
	}

	int ActiveChild()
	{
		return activeChild;
	}

protected:
	int			activeChild = 0;
	NodeList	children;
};

struct BTSequence : BTList
{
	virtual eBT Tick() override
	{
		switch (children[activeChild]->Tick())
		{
		case eBT::Success:
		{
			++activeChild;
			if (activeChild == children.size())
			{
				activeChild = 0;
				return eBT::Success;
			}
			else
			{
				return eBT::Continue;
			}
		} break;
		case eBT::Fail: { activeChild = 0; return eBT::Fail; } break;
		case eBT::Continue: { return eBT::Continue;	} break;
		case eBT::Abort: { activeChild = 0; return eBT::Abort; } break;
		}

		return eBT::Abort;
	}
};

struct BTSelector : BTList
{
	virtual eBT Tick() override
	{
		switch (children[activeChild]->Tick())
		{
		case eBT::Fail:
		{
			++activeChild;
			if (activeChild == children.size())
			{
				activeChild = 0;
				return eBT::Fail;
			}
			else
			{
				return eBT::Continue;
			}
		} break;
		case eBT::Success: { activeChild = 0; return eBT::Success; } break;
		case eBT::Continue: { return eBT::Continue;	} break;
		case eBT::Abort: { activeChild = 0; return eBT::Abort; } break;
		}

		return eBT::Abort;
	}
};

// 영역
struct BTBlock : BTList
{
	virtual eBT Tick() override
	{
		switch (children[activeChild]->Tick())
		{
		case eBT::Continue: { return eBT::Continue;	} break;
		default:
		{
			++activeChild;

			if (activeChild == children.size())
			{
				activeChild = 0;
				return eBT::Success;
			}

			return eBT::Continue;
		} break;
		}
	}
};

struct BTRoot : BTBlock
{
	bool bIsAbort = false;

	virtual eBT Tick() override
	{
		if (bIsAbort == true) { return eBT::Abort; } // 적당히 처리

		switch (children[activeChild]->Tick())
		{
		case eBT::Abort: { bIsAbort = true; eBT::Abort;	} break;
		case eBT::Continue: { return eBT::Continue;	} break;
		default:
		{
			++activeChild;

			if (activeChild == children.size())
			{
				activeChild = 0;
				return eBT::Success;
			}

			return eBT::Continue;
		} break;
		}

		return eBT::Abort;
	}
};

// 기능 수행
struct BTAction : BTNode
{
	using FP = std::function<void()>;
	FP fp;

	BTAction(const FP& a_fp)
	{
		fp = a_fp;
	}

	virtual eBT Tick() override
	{
		fp();
		return eBT::Success;
	}
};

struct BTCondition : BTNode
{
	using FP = std::function<bool()>;
	FP fp;

	BTCondition(const FP& a_fp)
	{
		fp = a_fp;
	}

	virtual eBT Tick() override
	{
		bool bResult = fp();

		return (bResult == true) ? eBT::Success : eBT::Fail;
	}
};

// 단일 노드를 자식으로 가지는 노드, Tick() 미 재정의. 추상 클래스
struct BTDecorator : BTNode
{
	BTNode* child = nullptr;

	BTDecorator(BTNode* c) : child(c) {}
	virtual ~BTDecorator() { delete child; child = nullptr; }
};

struct BTSwitch : BTDecorator
{
	BTSwitch(BTNode* c) : BTDecorator(c) {}

	eBT virtual Tick() override
	{
		eBT e = child->Tick();

		switch (e)
		{
		case eBT::Fail: return eBT::Success;
			break;
		case eBT::Success: return eBT::Fail;
			break;
		default:
			return e;
			break;
		}

		return eBT::Abort;
	}
};

CLOSE_NAMESPACE(BT_NODE)

namespace BT
{
	BT_NODE::BTRoot*		const Root();
	BT_NODE::BTSequence*	const Sequence();
	BT_NODE::BTSelector*	const Selector();
	BT_NODE::BTAction*		const Action(const BT_NODE::BTAction::FP& fp);
	BT_NODE::BTCondition*	const Condition(const BT_NODE::BTCondition::FP& fp);
	BT_NODE::BTSwitch*		const Switch(BT_NODE::BTNode* child);
};

