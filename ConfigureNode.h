#ifndef XML_CONFIGURE_NODE_HH
#define XML_CONFIGURE_NODE_HH
#include <Export.h>
#include <map>
#include <ConfigureVariant.h>

namespace xc{
    
    /**
     *
     */
    extern const char G[];

    /**
     *
     */
    extern const char C[];

    /**
     *
     */
    extern const char GOC[];

    /**
     *
     */
    extern const char policy_apply_on_node[];

    /**
     *
     */
    extern const char policy_apply_on_attr[];


    /**
     *
     */
    class configure_node;

    typedef struct _configure_attr_node{ 
        std::string name; 
        configure_variant variant; 
    }configure_attr_node;

    /**
     *
     */
    typedef std::vector<configure_attr_node> configure_attr_list;

    /**
     *
     */
    typedef std::vector<configure_node> configure_node_list;

    /**
     *
     */
    template<const char apply[], const char policy[]>
    struct policy_result_type {
        typedef typename void* result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_node, G>{
        typedef  configure_node& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_attr, G>{
        typedef  configure_variant& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_node, C>{
        typedef  configure_node& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_attr, C>{
        typedef  configure_variant& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_node, GOC>{
        typedef  configure_node& result_type;
    };

    /**
     *
     */
    template<>
    struct policy_result_type<policy_apply_on_attr, GOC>{
        typedef  configure_variant& result_type;
    };

    /**
     *
     */
    template<const char apply[], const char policy[]>
    struct visit_policy{
        typename policy_result_type<apply, policy>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    struct visit_policy<policy_apply_on_node, G>{
        policy_result_type<policy_apply_on_node, G>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    struct visit_policy<policy_apply_on_attr, G>{
        policy_result_type<policy_apply_on_attr, G>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    struct visit_policy<policy_apply_on_node, C>{
        policy_result_type<policy_apply_on_node, C>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    struct visit_policy<policy_apply_on_attr, C>{
        policy_result_type<policy_apply_on_attr, C>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    class visit_policy<policy_apply_on_node, GOC>{
        policy_result_type<policy_apply_on_node, GOC>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };

    /**
     *
     */
    template<>
    struct visit_policy<policy_apply_on_attr, GOC>{
        policy_result_type<policy_apply_on_attr, GOC>::result_type
            inline operator()(configure_node& self, const std::string& name);
    };



    /**
     *
     */
    class XCAPI configure_node{

        /**
         *
         */
    public:

        /**
         *
         */
        configure_node();

        /**
         *
         */
        configure_node(const std::string& name, const std::string& text = "");

        /**
         *
         */
        configure_node(const configure_node & node);

        /**
         *
         */
        configure_node& operator=(const configure_node& node);

        /**
         *
         */
        virtual ~configure_node();

        /**
         *
         */
    public:

        /**
         *
         */
        const std::string& text()const;

        /**
         *
         */
        void set_text(const std::string& text);

        /**
         *
         */
        const std::string& name()const;

        /**
         *
         */
        void set_name(const std::string& name);

        /**
         *
         */
    public:

        /**
         *
         */
		configure_variant& operator[](const char* attr_name);

        /**
         *
         */
		configure_variant& operator[](const std::string& attr_name);

		/**
		 *
		 */
		configure_variant& operator[](unsigned int index);

		/**
		 *
		 */
		configure_node& operator()(const char* field_name);

		/**
		 *
		 */
		configure_node& operator()(const std::string& field_name);

		/**
		 *
		 */
		configure_node& operator()(const char* field_name,unsigned int index);

		/**
		 *
		 */
		configure_node& operator()(const std::string& field_name,unsigned int index);

		/**
		 *
		 */
		configure_node& operator()(unsigned int index);

	public:
		/**
		 *
		 */
		//configure_node& operator[](const char*);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_node_list fields(const char* name);

        /**
         *
         */
        template<const char policy[] = G>
        configure_node& field(const char* name);

        /**
         * �����е����ýڵ��л�ȡֵ���ú�����readonly�ģ�ֻ�ṩ��ȡ���ܡ�
         * name     ����һ���������ƣ�
         * T        Ϊ��Ҫ���ص�����ֵ�����͡�
         * return   ��ȡ������ֵ
         */
        template< typename T >
        T attr(const char* name);

        /**
         * Ϊ���е����ýڵ�д����߸���һ�����Խڵ㡣
         * name     ��Ҫд����������ơ�
         * value    ��Ҫд�������ֵ.
         * return   ����ӵ�����ֵ�Ŀɱ����.
         */
        template< typename T >
        configure_node& attr(const char* name , const T& value);

        template<const char policy[] = C>
        configure_variant& attr(const char* name);


        /**
         *
         */
    public:

        /**
         *
         */
        configure_node* get_node(const std::string& name);

        /** 
         *
         */
        configure_node* create_node(const std::string& name);

        /**
         *
         */
        configure_node* get_or_create_node(const std::string& name);

        /**
         *
         */
        configure_variant* get_attr(const std::string& name);

        /**
         *
         */
        configure_variant* create_attr(const std::string& name);

        /**
         *
         */
        configure_variant* get_or_create_attr(const std::string& name);

		/**
         *
         */
		const configure_node_list& children()const;

		/**
         *
         */
		const configure_attr_list& attributes()const;

        /**
         *
         */
    protected:

        /**
         *
         */
        configure_attr_list _field;

        /**
         *
         */
        configure_node_list _children;

        /**
         *
         */
        std::string _name;

        /**
         *
         */
        std::string _text;
    };


    //=========================================================================
    //default policy
    //=========================================================================
    template<const char apply[], const char policy[]>
    typename policy_result_type<apply, policy>::result_type
        visit_policy<apply, policy>::
        operator()(configure_node& self, const std::string& name){
        typename policy_result_type<v_type, policy>::result_type result;
        return result;
    }

    //=========================================================================
    //G , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_node, G >::result_type
        visit_policy<policy_apply_on_node, G>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_node(name);
    }

    //=========================================================================
    //G , policy_apply_on_attr
    //=========================================================================
    policy_result_type<policy_apply_on_attr, G >::result_type
        visit_policy<policy_apply_on_attr, G>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_attr(name);
    }

    //=========================================================================
    //C , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_node, C>::result_type
        visit_policy<policy_apply_on_node, C>::
        operator()(configure_node& self, const std::string& name){
        return *self.create_node(name);
    }

    //=========================================================================
    //C , policy_apply_on_attr
    //=========================================================================
    policy_result_type<policy_apply_on_attr, C>::result_type
        visit_policy<policy_apply_on_attr, C>::
        operator()(configure_node& self, const std::string& name){
        return *self.create_attr(name);
    }

    //=========================================================================
    //GOC , policy_apply_on_node
    //=========================================================================
    policy_result_type<policy_apply_on_node, GOC>::result_type
        visit_policy<policy_apply_on_node, GOC>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_or_create_node(name);
    }

    //=========================================================================
    //GOC , policy_apply_on_attr
    //=========================================================================
    policy_result_type<policy_apply_on_attr, GOC>::result_type
        visit_policy<policy_apply_on_attr, GOC>::
        operator()(configure_node& self, const std::string& name){
        return *self.get_or_create_attr(name);
    }


    /**
     *
     */
    template<const char policy[]>
    configure_node& configure_node::field(const char* identity){
        return visit_policy<policy_apply_on_node, policy>()(*this, identity);
    }


    template< typename T >
    T configure_node::attr(const char* name){
        return visit_policy<policy_apply_on_attr, G>()(*this, name).cast<T>();
    }


    template< typename T >
    configure_node& configure_node::attr(const char* name, const T& value){
        visit_policy<policy_apply_on_attr, C>()(*this, name) = value;
        return *this;
    }

    template<const char policy[]>
    configure_variant& configure_node::attr(const char* name){
        return visit_policy<policy_apply_on_attr, policy>()(*this, name);
    }
}

#endif//XML_CONFIGURE_NODE_HH
