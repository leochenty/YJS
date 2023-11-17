#include "src/struct/BPlusTree.h"

namespace YJS_NAMESPACE {
    int memoryInternal = 8;// BPlusTree 's pointer
    int memoryLeaf = 0;
    int leafnum = 0;
    int internalnum = 0;
    char Pool[STRING_POOL_MAX + 1] = { '\0' };
    Id PoolId = {}; 
    int PoolSize = 0;
    int insertIndex = 0; 

    InternalNode::InternalNode()
    {
        parent = nullptr;
        offsetSum = 0;
    }

    InternalNode :: ~InternalNode() {}

    LeafNode::LeafNode()
    {
        isleaf = true;
        leftptr = nullptr;
        rightptr = nullptr;
        parent = nullptr;
    }

    LeafNode :: ~LeafNode() {}

    TreeNode::TreeNode()
    {
        parent = nullptr;
    }

    TreeNode::~TreeNode() {}

    void TreeNode::FreeChildren()
    {
        vector<TreeNode*> child = GetChild();
        for (unsigned int i = 0; i < child.size(); i++) {

            TreeNode* pNode = child[i];
            if (nullptr != pNode && !(pNode->isleaf)) {
                pNode->FreeChildren();
            }
            if (pNode != nullptr) {
                if (!(pNode->isleaf))
                {
                    int intersize = 9 + pNode->GetChild().size() * 8 + 4 + pNode->GetOffset().size() * 4;
                    memoryInternal += intersize;
                    internalnum++;
                }
                else
                {
                    int leaf = 9 + pNode->GetDeleted().size() * 2 + 40;
                    memoryLeaf += leaf;
                    leafnum++;
                }
                delete pNode;
            }
        }
    }

    BPlusTree::BPlusTree()
    {
        BT_root = nullptr;
    }

    BPlusTree::~BPlusTree()
    {
        if (nullptr != BT_root) {
            BT_root->FreeChildren();
            if (BT_root != nullptr) {
                memoryInternal += 9 + BT_root->GetChild().size() * 8 + 4 + BT_root->GetOffset().size() * 4;
                delete BT_root;
            }
        }
        BT_root = nullptr;
        std::cout << std::endl;
        cout << "-------------B+ Tree:----------------" << endl;
        cout << "InternalNodeNum: " << internalnum << endl;
        cout <<"InternalNode size: "<< memoryInternal / 1024<< "KB" << endl;
        cout << "LeafNum: " << leafnum << endl;
        cout <<"LeafNode size: "<< memoryLeaf / 1024<< "KB" << endl;
        cout <<"Total size: "<< (memoryInternal + memoryLeaf) / 1024<< "KB" << endl;
    }

    Id BPlusTree::getId(ItemPtr itemPtr) const
    {
        return itemPtr.first->headId + itemPtr.second;;
    }

    pair<int, TreeNode*> BPlusTree::getLeafByPos(int pos)const
    {
        tuple<int, TreeNode*, stack<int>> result = getShiftByPos(pos);
        int remain = get<0>(result);
        if (remain > 0) {
            if (remain == get<1>(result)->GetNode().size() + 1) remain--;
            return { remain - 1, get<1>(result) };
        }
        else
        {
            //cout << "node not found" << endl;
            return { 0, nullptr };
        }
    }


    tuple<int, TreeNode*, stack<int>> BPlusTree::getShiftByPos(int pos) const {

        stack<int> path;
        if (BT_root == nullptr) {
            return make_tuple(0, nullptr, path);
        }

        TreeNode* cursor = BT_root;
        int remain = pos + 1; 
        // insert in the end
		if ((remain -1) == cursor->GetSum())
		{
            vector<unsigned int> offset;
			int i = 0;
			while (!cursor->isleaf)
			{
				offset = cursor->GetOffset();
				for (i = offset.size() - 1; i >= 0; i--) {
					if (offset[i] != 0)
					{
						path.push(i);
						cursor = cursor->GetChild()[i];
						break;
					}
				}

			}
            return make_tuple(cursor->GetNode().size() + 1, cursor, path);
		}
		else
		{
			while (!(cursor->isleaf))
			{
				int i = 0;
				vector<unsigned int> offsetList = cursor->GetOffset();
				for (; i < (int)offsetList.size(); i++)
				{
					int offset = offsetList[i];
					remain -= offset;
					if (remain <= 0) {

						remain += offset;
						break;
					}

				}
				path.push(i);
				cursor = cursor->GetChild()[i];
			}
            int len = 0;
            vector<char>isdeleted =  cursor->GetDeleted();
            while (remain > 0)
            {
                if (isdeleted[len] == 0)
                {
                    remain--;
                }
                len++;
            }
			return make_tuple(len, cursor, path);
		}
    }


    void BPlusTree::insert(int pos, Context contents, Id gid)
    {
        tuple<int, TreeNode*, stack<int>> searchInfo = getShiftByPos(pos);
        int splitIdx = get<0>(searchInfo) - 1; // 
        TreeNode* originLeaf = get<1>(searchInfo);
        stack<int> path = get<2>(searchInfo);

        TreeNode* insertLeaf = new LeafNode;
        unsigned int idx = contents.size();
        insertLeaf->SetNode(contents);
        vector<char> isdeleted(idx, 0);
        insertLeaf->SetDeleted(isdeleted);
        insertLeaf->SetGID(gid); 
        TreeNode* rightLeaf = nullptr;

        if (originLeaf == nullptr) {
            BT_root = new InternalNode;

            insertLeaf->SetLeftOfLeaf(nullptr);
            insertLeaf->SetRightOfLeaf(nullptr);
            insertLeaf->parent = BT_root;

            vector<TreeNode*> children = { insertLeaf };
            BT_root->SetChild(children);

            vector<unsigned int> offsetList = { idx };
            BT_root->SetOffset(offsetList); 
            BT_root->SetSum(idx);

        }
        else {
            TreeNode* parent = originLeaf->parent;
            insertLeaf->parent = parent;
            int len = 0;
            vector<char> isdeleted = originLeaf->GetDeleted();
            for (int i = 0; i < splitIdx; i++)
            {
                len += (int)isdeleted[i];
            }
            if ((splitIdx-len) == 0) {
                insertLeaf->SetRightOfLeaf(originLeaf);
                insertLeaf->SetLeftOfLeaf(originLeaf->GetLeftOfLeaf());
                if (originLeaf->GetLeftOfLeaf() != nullptr)
                {
                    originLeaf->GetLeftOfLeaf()->SetRightOfLeaf(insertLeaf);
                }
                originLeaf->SetLeftOfLeaf(insertLeaf);
                updateLeafParent(insertLeaf, originLeaf, nullptr, parent, path.top(), idx);
            }
            else {
                insertLeaf->SetLeftOfLeaf(originLeaf);

                if (splitIdx == (int)originLeaf->GetNode().size()) {
                    insertLeaf->SetRightOfLeaf(originLeaf->GetRightOfLeaf());
                    if (originLeaf->GetRightOfLeaf() != nullptr)
                    {
                        originLeaf->GetRightOfLeaf()->SetLeftOfLeaf(insertLeaf);
                    }
                }
                else {
                    rightLeaf = new LeafNode;
                    Id gid(originLeaf->GetGID().client, originLeaf->GetGID().clock + splitIdx);
                    rightLeaf->SetGID(gid);

                    vector<char>originDeleted = originLeaf->GetDeleted();
                    originDeleted.assign(originDeleted.begin() + splitIdx, originDeleted.end());
                    rightLeaf->SetNode(originLeaf->GetNode().substr(splitIdx));
                    rightLeaf->SetDeleted(originDeleted);

                    rightLeaf->parent = parent;
                    rightLeaf->SetLeftOfLeaf(insertLeaf);
                    rightLeaf->SetRightOfLeaf(originLeaf->GetRightOfLeaf());
                    if (originLeaf->GetRightOfLeaf() != nullptr)
                    {
                        originLeaf->GetRightOfLeaf()->SetLeftOfLeaf(rightLeaf);
                    }          
                    insertLeaf->SetRightOfLeaf(rightLeaf);

                    originDeleted = originLeaf->GetDeleted();
                    originDeleted.assign(originDeleted.begin(), originDeleted.begin() + splitIdx);
                    originLeaf->SetDeleted(originDeleted);
                    originLeaf->SetNode(originLeaf->GetNode().substr(0, splitIdx));
                }

                originLeaf->SetRightOfLeaf(insertLeaf);
                updateLeafParent(originLeaf, insertLeaf, rightLeaf, parent, path.top(), idx);

            }

            path.pop();
            insertInternal(parent, path, idx);
        }
    }

    void BPlusTree::deleteItem(Index pos)
    {
        checkPool();
        tuple<int, TreeNode*, stack<int>> pair = getShiftByPos(pos);
        TreeNode* originLeaf = get<1>(pair);
        int splitIdx = get<0>(pair) - 1;
        stack<int> path = get<2>(pair);

        TreeNode* parent = originLeaf->parent;
        string vec = originLeaf->GetNode();
        vector<char> isdeleted = originLeaf->GetDeleted();
        isdeleted[splitIdx] = true;
        originLeaf->SetDeleted(isdeleted);
        //TreeNode* rightLeaf = nullptr;

        //if (splitIdx != (int)(vec.size() - 1)) {
        //    rightLeaf = new LeafNode;
        //    Id gid(originLeaf->GetGID().client, originLeaf->GetGID().clock + splitIdx + 1);
        //    rightLeaf->SetGID(gid);
        //    vector<char>originDeleted = originLeaf->GetDeleted();
        //    originDeleted.assign(originDeleted.begin() + splitIdx + 1, originDeleted.end());
        //    rightLeaf->SetNode(originLeaf->GetNode().substr(splitIdx + 1));
        //    rightLeaf->SetDeleted(originDeleted);

        //    rightLeaf->parent = parent;
        //    rightLeaf->SetLeftOfLeaf(originLeaf);
        //    rightLeaf->SetRightOfLeaf(originLeaf->GetRightOfLeaf());
        //    if (originLeaf->GetRightOfLeaf()!= nullptr)
        //    {
        //        originLeaf->GetRightOfLeaf()->SetLeftOfLeaf(rightLeaf);
        //    }
        //    originDeleted = originLeaf->GetDeleted();
        //    originDeleted.assign(originDeleted.begin(), originDeleted.begin() + splitIdx + 1);
        //    originLeaf->SetDeleted(originDeleted);
        //    originLeaf->SetNode(originLeaf->GetNode().substr(0, splitIdx + 1));

        //    originLeaf->SetRightOfLeaf(rightLeaf);
        //}

        int updateIdx = path.top();
        path.pop();
        int len = 0;
        for (char del : originLeaf->GetDeleted())
        {
            len += (int)del;
        }
        vector<unsigned int> offset = parent->GetOffset();
        offset[updateIdx] = originLeaf->GetNode().size() - len;
        parent->SetOffset(offset);
        parent->SetSum(parent->GetSum() -1);

 /*       if (rightLeaf != nullptr) {
            offset = parent->GetOffset();
            int len = 0;
            for (char det : rightLeaf->GetDeleted())
            {
                len += (int)det;
            }
            offset.insert(offset.begin() + updateIdx + 1, (int)(rightLeaf->GetNode().size()-len));
            parent->SetOffset(offset);
            vector<TreeNode*> child = parent->GetChild();
            child.insert(child.begin() + updateIdx + 1, rightLeaf);
            parent->SetChild(child);
        }*/

        insertInternal(parent, path, -1); 
    }

    void BPlusTree::insertInternal(TreeNode* cursor, stack<int> path, int length) {
        if ((int)cursor->GetOffset().size() <= MAX_INTERNAL_SIZE) {
            while (cursor->parent != nullptr)
            {
                cursor = cursor->parent;
                int updateIdx = path.top();
                path.pop();

                vector<unsigned int> offset = cursor->GetOffset();
                offset[updateIdx] += length;
                cursor->SetOffset(offset);
                cursor->SetSum(cursor->GetSum() + length);
            }
        }
        else {
            if (cursor->parent == nullptr) {
                TreeNode* newRoot = new InternalNode;
                vector<TreeNode*> child = { cursor };
                vector<unsigned int> offset = { cursor->GetSum() };
                newRoot->SetChild(child);
                newRoot->SetOffset(offset);
                newRoot->SetSum(cursor->GetSum() - length);
                BT_root = newRoot;
                cursor->parent = BT_root;
                path.push(0);
            }


            int splitIdx = ((int)cursor->GetOffset().size()) / 2;

            TreeNode* rightInt = new InternalNode;
            vector<TreeNode*> child = cursor->GetChild();
            child.assign(child.begin() + splitIdx, child.end());
            rightInt->SetChild(child);

            vector<unsigned int> offset = cursor->GetOffset();
            offset.assign(offset.begin() + splitIdx, offset.end());
            rightInt->SetOffset(offset);

            rightInt->parent = cursor->parent;
            int offsetSum = 0;
            for (int i = 0; i < splitIdx; i++) {
                offsetSum += cursor->GetOffset()[i];
            }
            rightInt->SetSum(cursor->GetSum() - offsetSum);
            for (TreeNode* node : rightInt->GetChild())
            {
                node->parent = rightInt;
            }

            offset = cursor->GetOffset();
            offset.assign(offset.begin(), offset.begin() + splitIdx);
            cursor->SetOffset(offset);

            child = cursor->GetChild();
            child.assign(child.begin(), child.begin() + splitIdx);
            cursor->SetChild(child);

            cursor->SetSum(offsetSum);

            TreeNode* parent = cursor->parent;
            int updateIdx = path.top();
            path.pop();

            offset = parent->GetOffset();
            offset[updateIdx] = cursor->GetSum();
            offset.insert(offset.begin() + updateIdx + 1, rightInt->GetSum());
            parent->SetOffset(offset);

            child = parent->GetChild();
            child.insert(child.begin() + updateIdx + 1, rightInt);
            parent->SetChild(child);

            parent->SetSum(parent->GetSum() + length);

            insertInternal(parent, path, length);
        }
    }

    void BPlusTree::updateLeafParent(TreeNode* leftLeaf, TreeNode* middleLeaf, TreeNode* rightLeaf, TreeNode* parent, int updateIdx, int length)
    {
        vector<unsigned int> offset = parent->GetOffset();
        int len = 0;
        for (char det : leftLeaf->GetDeleted())
        {
            len += (int)det;
        }
        offset[updateIdx] = (int)(leftLeaf->GetNode().size() - len);
        vector<TreeNode*> child = parent->GetChild();
        child[updateIdx] = leftLeaf;

        parent->SetOffset(offset);
        parent->SetChild(child);

        child.insert(child.begin() + updateIdx + 1, middleLeaf);
        parent->SetChild(child);

        len = 0;
        for (char det : middleLeaf->GetDeleted())
        {
            len += (int)det;
        }
        int middleOffsetNum = (int)middleLeaf->GetNode().size()-len;
        offset.insert(offset.begin() + updateIdx + 1, middleOffsetNum);
        parent->SetOffset(offset);

        int parentOffsetSum = parent->GetSum();
        parent->SetSum(parentOffsetSum + length);

        if (rightLeaf != nullptr)
        {
            child.insert(child.begin() + updateIdx + 2, rightLeaf);
            parent->SetChild(child);
            len = 0;
            for (char det:rightLeaf->GetDeleted())
            {
                len += (int)det;
            }
            int middleOffset = (int)(rightLeaf->GetNode().size()-len);
            offset.insert(offset.begin() + updateIdx + 2, middleOffset);
            parent->SetOffset(offset);
        }
    }

    void BPlusTree::display()
    {
        TreeNode* cursor = BT_root;
        if (cursor == nullptr) {
            return;
        }
        deque<TreeNode*> deque;
        deque.push_front(cursor);

        while (!deque.empty()) {
            int size = (int)deque.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = deque.front();
                deque.pop_front();

                if (!node->isleaf) {
                    for (int val : node->GetOffset()) {
                        cout << val << " ";
                    }
                    cout << "|| ";

                    for (TreeNode* v : node->GetChild()) {
                        deque.push_back(v);
                    }
                }
                else {
                    cout << "(" << node->GetGID().client << "," << node->GetGID().clock << ")";
                    for (char n : node->GetNode()) {
                        cout << n;
                    }
                    for (char ch : node->GetDeleted())
                    {
                        cout << ((int)ch == 1 ? '0' : '1');
                    }
                    cout << "|| ";
                }
            }
            cout << endl;
        }
    }
    ItemPtr BPlusTree::begin() const
    {
        pair<int, TreeNode*> res = getLeafByPos(0);
        ItemListInterface* mbegin = (LeafNode*)res.second;
        ItemPtr beginPtr = { mbegin, res.first };
        return beginPtr;
    }

    ItemPtr BPlusTree::end() const
    {
        //TreeNode* cursor = BT_root;
        //while (cursor != nullptr && !(cursor->isleaf))
        //{
        //    cursor = cursor->GetChild().back();
        //}
        //ItemListInterface* mend = (LeafNode*)cursor;
        //ItemPtr endPtr;
        //if (mend != nullptr)
        //{
        //    endPtr = make_pair(mend, mend->context.size() - 1);
        //}
        //else
        //{
        //    endPtr = make_pair(nullptr, 0);
        //}
        //return endPtr;
        return { nullptr, 0 };
    }

    void BPlusTree::insertItem(Index index, ItemMessage itemMsg)
    {
        if (PoolSize == 0) {
            PoolId = itemMsg.id;
            insertIndex = index;
        }
        
        char ch = itemMsg.character;
        Id id = itemMsg.id;
        if (id.client == PoolId.client && id.clock == PoolId.clock && index == insertIndex)
        {
            if (PoolSize < STRING_POOL_MAX)
            {
                Pool[PoolSize] = ch;
                PoolSize++;
            }
            else
            {
                id.clock -= PoolSize;
                string contents = Pool;
                insert(insertIndex - PoolSize, contents, id);
                for (int i = 0; i < PoolSize; i++) { Pool[i] = '\0'; }
                Pool[0] = ch;
                PoolSize = 1;
            }
            insertIndex++;
            PoolId.clock++;
            
        }
        else
        {
            PoolId.clock -= PoolSize;
            string contents = Pool;
            insert(insertIndex - PoolSize, contents, PoolId);
            PoolId = id;
            insertIndex = index + 1;
            PoolId.clock++;
            for (int i = 0; i < PoolSize; i++) { Pool[i] = '\0'; }
            Pool[0] = ch;
            PoolSize = 1;
        }
        
        //insert(index, string(1, itemMsg.character), itemMsg.id);
    }


    ItemPtr BPlusTree::getItemByPos(Index index) const
    {
        if (PoolSize != 0 && index >= (insertIndex - PoolSize) && index < insertIndex) {
            LeafNode leaf;
            int offset = index - (insertIndex - PoolSize);
            leaf.context = Pool[offset];
            Id id = PoolId;
            id.clock -= offset;
            leaf.SetGID(id);
            ItemListInterface* Item = &leaf;
            return make_pair(Item, offset);
        }
        else
        {   
            if (PoolSize != 0 && index >= (insertIndex - PoolSize))
            {
                index -= PoolSize;
            }
            pair<int, TreeNode*> res = getLeafByPos(index);
            TreeNode* leaf = res.second;
            ItemListInterface* Item = (LeafNode*)leaf;
            return make_pair(Item, res.first);
        }

    }

    ItemPtr BPlusTree::predecessor(ItemPtr itemPtr) const
    {
        unsigned int offset = itemPtr.second;
        LeafNode* p = (LeafNode*)itemPtr.first;
        do
        {
            while (offset > 0)
                if (p->GetDeleted()[--offset] == 0)
                    return { p, offset };
            p = (LeafNode*)p->GetLeftOfLeaf();
            offset = p->GetNode().size();
        } while (p);

        return this->end();
    }

    ItemPtr BPlusTree::successor(ItemPtr itemPtr) const
    {
        int offset = itemPtr.second;
        LeafNode* p = (LeafNode*)itemPtr.first;
        do
        {
            while (++offset < (p->GetNode().size())) {
                if (p->GetDeleted()[offset] == 0)
                    return { p, offset };
            }

            offset = -1;
            p = (LeafNode*)p->GetRightOfLeaf();
        } while (p);

        return {nullptr, 0};
    }

    void BPlusTree::checkPool()
    {
        if (PoolSize > 0)
        {
            Id id = PoolId;
            id.clock -= PoolSize;
            string contents = Pool;
            insert(insertIndex - PoolSize, contents, id);
            for (int i = 0; i < PoolSize; i++) { Pool[i] = '\0'; }
            PoolSize = 0;
        }
    }
}