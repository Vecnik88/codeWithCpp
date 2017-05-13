// Created by Vecnik88

/*
                Множество с запросами суммы на отрезке

    Реализуйте структуру данных для хранения множества целых чисел,
    поддерживающую запросы добавления, удаления, поиска, а также
    суммы на отрезке. На вход в данной задаче будет дана последова-
    тельность таких запросов. Чтобы гарантировать, что ваша программа
    обрабатывает каждый запрос по мере поступления (то есть онлайн),
    каждый запрос будет зависеть от результата выполнения одного из
    предыдущих запросов. Если бы такой зависимости не было, задачу
    можно было бы решить оффлайн: сначала прочитать весь вход и
    сохранить все запросы в каком-нибудь виде, а потом прочитать вход
    ещё раз, параллельно отвечая на запросы.
    Формат входа. Изначально множество пусто. Первая строка содер-
    жит число запросов n. Каждая из n следующих строк содержит
    запрос в одном из следующих четырёх форматов:
    • + i: добавить число f(i) в множество (если оно уже есть,
    проигнорировать запрос);
    • - i: удалить число f(i) из множества (если его нет, про-
    игнорировать запрос);
    • ? i: проверить принадлежность числа f(i) множеству;
    • s l r: посчитать сумму всех элементов множества,
    попадающих в отрезок [f(l), f(r)].
    Функция f определяется следующим образом. Пусть s — резуль-
    тат последнего запроса суммы на отрезке (если таких запросов
    ещё не было, то s = 0). Тогда
    f(x) = (x + s) mod 1 000 000 001 .
    Формат выхода. Для каждого запроса типа ? i выведите «Found»
    или «Not found». Для каждого запроса суммы выведите сумму
    всех элементов множества, попадающих в отрезок [f(l), f(r)].
    Гарантируется, что во всех тестах f(l) ≤ f(r).
    Ограничения. 1 ≤ n ≤ 105; 0 ≤ i ≤ 109.

    Пример.
    Вход:
    15
    ? 1
    + 1
    ? 1
    + 2
    s 1 2
    + 1000000000
    ? 1000000000
    - 1000000000
    ? 1000000000
    s 999999999 1000000000
    - 2
    ? 2
    - 0
    + 9
    s 0 9
    Выход:
    Not found
    Found
    3
    Found
    Not found
    1
    Not found
    10
    Для первых пяти запросов s = 0, для следующих пяти — s = 3,
    для следующих пяти — s = 1. Заданные запросы разворачива-
    ются в следующие: find(1), add(1), find(1), add(2), sum(1, 2) → 3,
    add(2), find(2) → Found, del(2), find(2) → Not found, sum(1, 2) → 1,
    del(3), find(3) → Not found, del(1), add(10), sum(1, 10) → 10.
    Добавление элемента дважды не изменяет множество, как и попытки
    удалить элемент, которого в множестве нет.

    Пример.
    Вход:
    5
    ? 0
    + 0
    ? 0
    - 0
    ? 0
    Выход:
    Not found
    Found
    Not found
    Пример.
    Вход:
    5
    + 491572259
    ? 491572259
    ? 899375874
    s 310971296 877523306
    + 352411209
    Выход:
    Found
    Not found
    491572259

*/

#include <iostream>

template<typename T>class AVLtree {
public:

    struct Node {
        struct Node *parrent, *left, *right;
        size_t hight;
        T val;
        T sum;
        size_t cnt;

        Node(T & val, struct Node *parrent = nullptr):parrent(parrent), left(nullptr), right(nullptr), hight(1), val(val), sum(val), cnt(1) {}

        Node(const Node & other) {
            if(other.left != nullptr) {
                left = new struct Node(other.left);
                left->parrent = this;
            } else
                left = nullptr;

            if(other.right != nullptr) {
                right = new struct Node(other.right);
                right->parrent = this;
            } else
                right = nullptr;

            val = other.val;
            sum = other.sum;
            cnt = other.cnt;
            hight = other.hight;
            parrent = nullptr;
        }

        struct Node & operator=(const struct Node & other) {
            if(this != &other) {
                delete left;
                if(other.left != nullptr) {
                    left = new struct Node(other.left);
                    left->parrent = this;
                } else
                    left = nullptr;

                delete right;
                if(other.right != nullptr) {
                    right = new struct Node(other.right);
                    right->parrent = this;
                } else
                    right = nullptr;

                val = other.val;
                sum = other.sum;
                cnt = other.cnt;
                hight = other.hight;
                parrent = nullptr;
            }
            return *this;
        }

        ~Node() {
            delete left, right;
            left = right = nullptr;
            cnt = hight = 1;
        }

        size_t left_hight() const {
            if(left == nullptr)
                return T();
            else
                return left->hight;
        }
        size_t right_hight() const {
            if(right == nullptr)
                return T();
            else
                return right->hight;
        }
        size_t left_cnt() const {
            if(left == nullptr)
                return 0;
            else
                return left->cnt;
        }
        size_t right_cnt() const {
            if(right == nullptr)
                return 0;
            else
                return right->cnt;
        }
        const T left_sum() const {
            if(left == nullptr)
                return T();
            else
                return left->sum;
        }
        const T right_sum() const {
            if(right == nullptr)
                return T();
            else
                return right->sum;
        }
        void update() {
            cnt = 1   + this->left_cnt() + this->right_cnt();
            sum = val + this->left_sum() + this->right_sum();
            hight = this->left_hight();
            size_t tmp = this->right_hight();
            hight = 1 + (hight > tmp ? hight : tmp);
        }
    };
private:
    struct Node * root;
    void check(struct Node * a) {
        do {
            if(a->left_hight() + 1 < a->right_hight()) {
                struct Node * b = a->right;
                if(b->left_hight() <= b->right_hight()) {
                    if(a->parrent == nullptr)
                        root = b;
                    else if(a->parrent->left == a)
                        a->parrent->left = b;
                    else if(a->parrent->right == a)
                        a->parrent->right = b;
                    b->parrent = a->parrent;

                    a->right = b->left;
                    if(a->right != nullptr)
                        a->right->parrent = a;

                    b->left = a;
                    a->parrent = b;
                    a->update();
                    b->update();

                    a = b;
                } else {
                    struct Node * b = a->right, *c = b->left;
                    if(a->parrent == nullptr)
                        root = c;
                    else if(a->parrent->left == a)
                        a->parrent->left = c;
                    else if(a->parrent->right == a)
                        a->parrent->right = c;
                    c->parrent = a->parrent;

                    a->right = c->left;
                    if(a->right != nullptr)
                        a->right->parrent = a;

                    b->left = c->right;
                    if(b->left != nullptr)
                        b->left->parrent = b;

                    a->parrent = c;
                    c->left = a;

                    b->parrent = c;
                    c->right = b;
                    a->update();
                    b->update();
                    c->update();

                    a = c;
                }
            } else if(a->left_hight() > a->right_hight() + 1) {
                struct Node * b = a->left;
                if(b->left_hight() >= b->right_hight()) {
                    if(a->parrent == nullptr)
                        root = b;
                    else if(a->parrent->left == a)
                        a->parrent->left = b;
                    else if(a->parrent->right == a)
                        a->parrent->right = b;
                    b->parrent = a->parrent;

                    a->left = b->right;
                    if(a->left != nullptr)
                        a->left->parrent = a;

                    b->right = a;
                    a->parrent = b;
                    a->update();
                    b->update();

                    a = b;
                } else {
                    struct Node * b = a->left, *c = b->right;
                    if(a->parrent == nullptr)
                        root = c;
                    else if(a->parrent->left == a)
                        a->parrent->left = c;
                    else if(a->parrent->right == a)
                        a->parrent->right = c;
                    c->parrent = a->parrent;

                    a->left = c->right;
                    if(a->left != nullptr)
                        a->left->parrent = a;

                    b->right = c->left;
                    if(b->right != nullptr)
                        b->right->parrent = b;

                    a->parrent = c;
                    c->right = a;

                    b->parrent = c;
                    c->left = b;
                    a->update();
                    b->update();
                    c->update();

                    a = c;
                }
            } else
                a->update();
            a = a->parrent;
        } while(a != nullptr);

#ifdef _WIN32
        struct Node *pmin, *pmax;
        size_t cnt;
        if(root != nullptr && check_Get_min_max(root, &pmin, &pmax, &cnt) && root->cnt==cnt)
            std::cerr << "CORRECT" << std::endl;
        else
            std::cerr << "INCORRECT" << std::endl;
#endif
    }
    bool check_Get_min_max(struct Node * nd, struct Node ** ppmin, struct Node ** ppmax, size_t * cnt) const{
        bool is_ok = true;
        struct Node * pmin, *pmax;
        size_t cnt_l=0, cnt_r=0;

        if(nd->left !=nullptr) {
            is_ok = check_Get_min_max(nd->left, &pmin, &pmax, &cnt_l)
                && pmax->val < nd->val;
            *ppmin = pmin;
        } else
            *ppmin = nd;


        if(is_ok && nd->right !=nullptr) {
            is_ok = check_Get_min_max(nd->right, &pmin, &pmax, &cnt_r)
                && nd->val <= pmin->val;
            *ppmax = pmax;
        } else
            *ppmax = nd;

        *cnt = 1 + cnt_l + cnt_r;
        is_ok = is_ok && *cnt == nd->cnt;

        return is_ok;
    }
public:
    AVLtree():root(nullptr) {}
    AVLtree(const AVLtree & other) {
        if(other.root != nullptr) {
            root = new struct Node(other.root);
        } else
            root = nullptr;
    }
    AVLtree & operator=(const AVLtree & other) {
        if(this != &other) {
            delete root;
            if(other.root != nullptr) {
                root = new struct Node(other.root);
            } else
                root = nullptr;
        }
        return *this;
    }
    const struct Node * operator[](size_t i) const {
        struct Node * is_ok = nullptr;
        if(root != nullptr) {
            struct Node * cur = root;
            bool is_repeat = true;
            do {
                if(cur->left_cnt() == i) {
                    is_ok = cur;
                    is_repeat = false;
                } else if(cur->left_cnt() < i) {
                    i -= cur->left_cnt() + 1;
                    if(cur->right != nullptr)
                        cur = cur->right;
                    else
                        is_repeat = false;
                } else if(cur->left != nullptr)
                    cur = cur->left;
                else
                    is_repeat = false;
            } while(is_repeat);
        }

        return is_ok;
    }
    ~AVLtree() {
        delete root;
    }
    void add(T & val) {
        if(root == nullptr) {
            root = new struct Node(val);
        } else {
            struct Node * cur = root;
            bool is_repeat = true, is_check=true;
            do {
                if(cur->val == val)
                    is_check = is_repeat = false;
                else if(cur->val < val) {
                    if(cur->right != nullptr)
                        cur = cur->right;
                    else {
                        cur->right = new struct Node(val, cur);
                        is_repeat = false;
                    }
                } else if(cur->left != nullptr) {
                    cur = cur->left;
                } else {
                    cur->left = new struct Node(val, cur);
                    is_repeat = false;
                }
            } while(is_repeat);

            if(is_check)
                check(cur);
        }
    }
    const struct Node * find(const T & val) const{
        struct Node * is_ok = nullptr;
        if(root != nullptr) {
            struct Node * cur = root;
            bool is_repeat = true;
            do {
                if(cur->val == val) {
                    is_ok = cur;
                    is_repeat = false;
                } else if(cur->val < val) {
                    if(cur->right != nullptr)
                        cur = cur->right;
                    else
                        is_repeat = false;
                } else if(cur->left != nullptr)
                    cur = cur->left;
                else
                    is_repeat = false;
            } while(is_repeat);
        }

        return is_ok;
    }
    T  sum(const T & b, const T & e) const {
        T s = 0;

        if(root != nullptr) {
            struct Node * cur = root;
            do {
                if(cur->val < b) {
                    cur = cur->right;
                } else if(e < cur->val) {
                    cur = cur->left;
                } else {
                    s = cur->val;
                    struct Node * tmp = cur->left;
                    while(tmp!=nullptr) {
                        if(b == tmp->val) {
                            s += tmp->val + tmp->right_sum();
                            tmp = nullptr;
                        }else if(b < tmp->val) {
                            s += tmp->val + tmp->right_sum();
                            tmp = tmp->left;
                        } else
                            tmp = tmp->right;
                    }
                    tmp = cur->right;
                    while(tmp != nullptr) {
                        if(e == tmp->val) {
                            s += tmp->val + tmp->left_sum();
                            tmp = nullptr;
                        } else if(tmp->val < e) {
                            s += tmp->val + tmp->left_sum();
                            tmp = tmp->right;
                        } else
                            tmp = tmp->left;
                    }
                    cur = nullptr;
                }
            } while(cur != nullptr);
        }

        return s;
    }
    void del(const T & val) {
        if(root != nullptr) {
            struct Node * cur = root;
            bool is_repeat = true;
            do {
                if(cur->val == val) {
                    struct Node * a = nullptr;
                    if(cur->left == nullptr && cur->right == nullptr) {
                        if(cur->parrent == nullptr)
                            root = nullptr;
                        else if(cur->parrent->left == cur)
                            cur->parrent->left = nullptr;
                        else if(cur->parrent->right == cur)
                            cur->parrent->right = nullptr;
                        a = cur->parrent;
                    } else if(cur->left == nullptr) {
                        if(cur->parrent == nullptr)
                            root = cur->right;
                        else if(cur->parrent->left == cur)
                            cur->parrent->left = cur->right;
                        else if(cur->parrent->right == cur)
                            cur->parrent->right = cur->right;

                        if(cur->right != nullptr)
                            cur->right->parrent = cur->parrent;
                        cur->right = nullptr;
                        a = cur->parrent;
                    } else if(cur->right == nullptr) {
                        if(cur->parrent == nullptr)
                            root = cur->left;
                        else if(cur->parrent->left == cur)
                            cur->parrent->left = cur->left;
                        else if(cur->parrent->right == cur)
                            cur->parrent->right = cur->left;

                        if(cur->left != nullptr)
                            cur->left->parrent = cur->parrent;
                        cur->left = nullptr;
                        a = cur->parrent;
                    } else {
                        struct Node * r = cur->left;
                        while(r->right != nullptr)
                            r = r->right;
                        if(cur->parrent == nullptr)
                            root = r;
                        else if(cur->parrent->left == cur)
                            cur->parrent->left = r;
                        else if(cur->parrent->right == cur)
                            cur->parrent->right = r;
                        if(cur->left != r) {
                            r->parrent->right = r->left;
                            if(r->left!=nullptr)
                                r->left->parrent = r->parrent;

                            r->left = cur->left;
                            r->left->parrent = r;

                            a = r->parrent;
                        }else
                            a = r;

                        cur->left = nullptr;



                        r->parrent = cur->parrent;
                        r->right = cur->right;
                        r->right->parrent = r;
                        cur->right = nullptr;
                    }

                    if(a!=nullptr)
                        check(a);
                    delete cur;
                    is_repeat = false;
                } else if(cur->val < val) {
                    if(cur->right != nullptr)
                        cur = cur->right;
                    else
                        is_repeat = false;
                } else if(cur->left != nullptr)
                    cur = cur->left;
                else
                    is_repeat = false;
            } while(is_repeat);
        }
    }
    const struct Node * Root() const {
        return root;
    }
    void In_Order(std::ostream & out,const struct Node * nd = nullptr) const {
        if(nd == nullptr)
            nd = root;
        if(nd != nullptr) {
            if(nd->left != nullptr)
                In_Order(out, nd->left);

            out << nd->val << ' ';

            if(nd->right != nullptr)
                In_Order(out, nd->right);
        }
    }
    void Pre_Order(std::ostream & out, const struct Node * nd = nullptr) const {
        if(nd == nullptr)
            nd = root;
        if(nd != nullptr) {
            out << nd->val << ' ';

            if(nd->left != nullptr)
                In_Order(out, nd->left);

            if(nd->right != nullptr)
                In_Order(out, nd->right);
        }
    }
    void Post_Order(std::ostream & out, const struct Node * nd = nullptr) const {
        if(nd == nullptr)
            nd = root;
        if(nd != nullptr) {
            if(nd->left != nullptr)
                In_Order(out, nd->left);

            if(nd->right != nullptr)
                In_Order(out, nd->right);

            out << nd->val << ' ';
        }
    }
};

long long f(long long x, long long s) {
    x = (x + s) % 1000000001;
    return x;
}

int main() {
    unsigned n;
    std::cin >> n;

    long long s = 0, k, m;
    AVLtree<long long> tr;
    while(n) {
        char c;
        std::cin >> c >> k;
        k = f(k, s);
        if(c == '+')
            tr.add(k);
        else if(c == '-')
            tr.del(k);
        else if(c == '?')
            std::cout << (tr.find(k) != nullptr ? "Found" : "Not found") << std::endl;
        else if(c == 's') {
            std::cin >> m;
            m = f(m, s);
            s = tr.sum(k,m);
            std::cout << s << std::endl;
        }
        --n;

#ifdef _WIN32
        tr.In_Order(std::cerr);
        std::cerr << std::endl;
        if(tr[7]!=nullptr)
            std::cerr << tr[7]->val << std::endl;

#endif
    }
    return 0;
}
