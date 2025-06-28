#ifndef BTREE_H_
#define BTREE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

// とりあえずサンプル実装のため小さめにする。
#define BTREE_NODE_ENTRY_MAX (4)

typedef struct BTree BTree_t;
typedef struct BTree_Node BTree_Node_t;
typedef struct BTree_Entry BTree_Entry_t;
typedef struct BTree_Position BTree_Position_t;

// エントリとして、値とリンクを1つのデータとして持つが、2つに分けた方がいいかもしれない。
struct BTree_Entry
{
    // 子へのリンク
    // サンプル実装のため、ポインタとして保持する。共有メモリなどに配置することを考えると、何らかの番号(あるいはオフセット)が望ましい。
    BTree_Node_t *pChild;
    // サンプル実装のため、現状は単なるスカラー値を保持する。本来はキーと値へのポインタであるべき。
    int32_t value;
};

// ノード
struct BTree_Node
{
    // 親へのリンク
    // サンプル実装のため、ポインタとして保持する。共有メモリなどに配置することを考えると、何らかの番号(あるいはオフセット)が望ましい。
    BTree_Node_t *pParent;
    // エントリの数。有効な値の数。最後のリンクへの数は含まない。
    int32_t count;
    // エントリの配列
    // 配列の最後は子へのリンクのみを持つ。
    // リンク_0,値_0,リンク_1,値_1,...,値_n,リンク_{n+1} という構造になる。
    BTree_Entry_t entry[BTREE_NODE_ENTRY_MAX + 1];
};

// B-Tree
struct BTree
{
    // 全体としての件数
    int32_t count;
    // ルートとなるノードへのリンク
    BTree_Node_t *pRoot;
};

// B-Tree の中の位置を示すための構造体
typedef struct BTree_Position
{
    // ノードへのリンク
    BTree_Node_t *pNode;
    // ノード内の位置。
    // 値を指している場合は正のインデックス。
    // 枝を指している場合は -(index + 1) でそのエントリを指す。
    int index;
} BTree_Position_t;

typedef struct BTree_get_result
{
    bool found;
    // 値で検索して値を取得するのはナンセンスだが、これはサンプル実装のため
    int32_t value;
} BTree_get_result_t;

/// @brief Initialize
/// @param pThis instance
void BTree_initialize(BTree_t *pThis);

/// @brief Finalize
/// @param pThis instance
void BTree_finalize(BTree_t *pThis);

/// @brief Add value
/// @param pTree B-Tree inscance
/// @param value value
/// @return result
int BTree_add(BTree_t *pTree, int32_t value);

/// @brief Delete value
/// @param pTree B-Tree inscance
/// @param value value
/// @return result
int BTree_delete(BTree_t *pTree, int32_t value);

/// @brief Get value
/// @param pTree B-Tree inscance
/// @param value value
/// @return
BTree_get_result_t BTree_get(BTree_t *pTree, int32_t value);

/// @brief Validate B-Tree structure
/// @param pTree B-Tree inscance
void BTree_validate(BTree_t *pTree);

/// @brief Dump B-Tree
/// @param pTree B-Tree inscance
void BTree_dump(BTree_t *pTree);

/// @brief Validate B-Tree structure
/// @param pNode node
void BTree_Node_validate(BTree_Node_t *pNode);

/// @brief Create node
/// @return pointer to new node
BTree_Node_t *BTree_Node_create();

/// @brief Finalize node
/// @param pNode node
void BTree_Node_finalize(BTree_Node_t *pNode);

/// @brief Destroy node
/// @param pNode node
void BTree_Node_destroy(BTree_Node_t *pNode);

/// @brief Dump node
/// @param pTree B-Tree instance
/// @param pNode node
/// @param level indent level
/// @param recursive recursive flag
void BTree_Node_dump(BTree_t *pTree, BTree_Node_t *pNode, int level, bool recursive);

/// @brief Find edge in parent node
/// @param pNode node
/// @return edge index
int BTree_Node_findEdge(BTree_Node_t *pNode);

/// @brief Find entry
/// @param pNode node
/// @param value value
/// @param recursive recursive flag
/// @return position
BTree_Position_t BTree_Node_findEntry(BTree_Node_t *pNode, int32_t value, bool recursive);

/// @brief Insert entry to node
/// @param pTree B-Tree instance
/// @param pNode node
/// @param index entry index
/// @param value value
/// @param pChild new child
/// @return result
int BTree_Node_insertEntry(BTree_t *pTree, BTree_Node_t *pNode, int index, int32_t value, BTree_Node_t *pChild);

/// @brief Delete entry from node
/// @param pNode node
/// @param index entry index
void BTree_Node_deleteEntry(BTree_Node_t *pNode, int index);

/// @brief Merge node
/// @param pTree B-Tree instance
/// @param pNode node
/// @return result
int BTree_Node_merge(BTree_t *pTree, BTree_Node_t *pNode);

#endif // BTREE_H_
