#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>



#define _TAG_ do { printf("tag: %d : %s\n", __LINE__, __func__); } while (false)

////

struct ListNode {
    int val;
    struct ListNode *next;
};

void _show_list(int line, struct ListNode* list)
{
    #if 0
    printf("\n %d  -- ", line);
    while (list != NULL) {
        printf(" . %d", list->val);
        list = list->next;
    }
    printf("\n");
    #endif
}


#define show_list(list) _show_list(__LINE__, list)
#if 0
void show_list(struct ListNode* list) {
    printf("\n");
    while (list != NULL) {
        printf(" . %d", list->val);
        list = list->next;
    }
    printf("\n");
}
#endif


////

typedef struct ListNode ListNode;

struct Context {
    ListNode*   list;

    ListNode*   result_h;
    ListNode*   result_t;

    ListNode*   slice_h;
    ListNode*   slice_t;
};
typedef struct Context Context;


void ctx_cut(Context* ctx) {
    _TAG_;
    assert(ctx->list != NULL);

    ListNode* h = ctx->list;
    ListNode* t = ctx->list;
    while (t->next != NULL && t->next->val == h->val) {
        t = t->next;
    }
    // t->next == NULL or t->next->val != h->val

    if (t->next == NULL) {
        ctx->slice_h = h;
        ctx->slice_t = t;
        ctx->list = NULL;
        return;
    }

    ctx->list = t->next; // set ctx->list

    if (ctx->list->val < h->val) {
        t->next = NULL;

        while (ctx->list != NULL && ctx->list->val <= h->val) {
            _TAG_;
            ListNode* n = ctx->list;
            ctx->list = ctx->list->next; // set ctx->list
            n->next = h;
            h = n;
        }

        ctx->slice_h = h;
        ctx->slice_t = t;
        return;
    }

    else /* t->next->val > t->val */ {
        while (t->next != NULL && t->val <= t->next->val) {
            t = t->next;
        }

        ctx->list = t->next; // set ctx->list
        t->next = NULL;
        ctx->slice_h = h;
        ctx->slice_t = t;
        return;
    }
}

void ctx_init(Context* ctx, ListNode* list) {
    _TAG_;
    if (list != NULL && list->next != NULL) {
        ctx->list = list;

        ctx_cut(ctx);
        show_list(ctx->slice_h);

        ctx->result_h = ctx->slice_h;
        ctx->result_t = ctx->slice_t;
        ctx->slice_h = NULL;
        ctx->slice_t = NULL;
    }
    else {
        ctx->list = NULL;
        ctx->result_h = list;
        ctx->result_t = NULL; // incorrect, but we don't care
        ctx->slice_h = NULL;
        ctx->slice_t = NULL;
    }
}

void ctx_merge(Context* ctx) {
    _TAG_;

    ListNode* h = NULL;
    ListNode* a = NULL;
    ListNode* b = NULL;

    if (ctx->result_h->val < ctx->slice_h->val) {
        h = ctx->result_h;
        a = ctx->result_h;
        b = ctx->slice_h;
    }
    else {
        h = ctx->slice_h;
        a = ctx->slice_h;
        b = ctx->result_h;
    }

    // merge b to a
    while (b != NULL) {
        ListNode* n = b;
        b = b->next;
        //n->next = NULL;

        while (a->next != NULL && a->next->val <= n->val) {
            a = a->next;
        }

        if (a->next != NULL) /* a->next->val > n->val*/ {
            n->next = a->next;
            a->next = n;
            // Instead of doing this, we could be even better!
        }
        else /* a->val <= n->val && a->next == NULL */ {
            a->next = n;

            // b = NULL // ALL DONE!
            break;
        }
    }

    // done
    ctx->result_h = h;
    ctx->result_t = a;
    ctx->slice_h = NULL;
    ctx->slice_t = NULL;

    return;
}

struct ListNode* sortList(struct ListNode* head) {

    Context ctx;
    ctx_init(&ctx, head);

    while (ctx.list != NULL) {
        ctx_cut(&ctx);
        show_list(ctx.slice_h);
        ctx_merge(&ctx);
        show_list(ctx.result_h);
    }

    return ctx.result_h;
}


////

ListNode* make_list(int* a, size_t len) {
    ListNode result;
    ListNode* t = &result;

    for (int i = 0; i < len; ++i) {
        ListNode* n = malloc(sizeof(ListNode));
        n->val = a[i];
        n->next = NULL;
        t->next = n;
        t = t->next;
    }

    return result.next;
}

#include "data.c"

int main() {

    //int a[] = {4,2,1,3};
    //int a[] = {-1, 5, 3, 4, 0};
    //int a[] = {2,1};

    ListNode* list = make_list(BigArray, sizeof(BigArray) / sizeof(int));
    //show_list(list);

    ListNode* sorted = sortList(list);
    (void)sorted;
    //show_list(sorted);

    return 0;
}
