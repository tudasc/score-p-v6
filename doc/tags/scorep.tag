<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>SCOREP_MetricPlugins.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__MetricPlugins_8h</filename>
    <includes id="SCOREP__MetricTypes_8h" name="SCOREP_MetricTypes.h" local="no" imported="no">scorep/SCOREP_MetricTypes.h</includes>
    <class kind="struct">SCOREP_Metric_Plugin_Info</class>
    <class kind="struct">SCOREP_Metric_Plugin_MetricProperties</class>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_METRIC_PLUGIN_ENTRY</name>
      <anchorfile>SCOREP__MetricPlugins_8h.html</anchorfile>
      <anchor>a6107d9468ac980a94ad707bd40a40e40</anchor>
      <arglist>(_name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_METRIC_PLUGIN_VERSION</name>
      <anchorfile>SCOREP__MetricPlugins_8h.html</anchorfile>
      <anchor>a19947f3f006b54f239f9131e32191392</anchor>
      <arglist></arglist>
      <docanchor file="SCOREP__MetricPlugins_8h" title="Mandatory functions">mandatoryF</docanchor>
      <docanchor file="SCOREP__MetricPlugins_8h" title="Mandatory variables">mandatoryV</docanchor>
      <docanchor file="SCOREP__MetricPlugins_8h" title="Optional functions">optionalF</docanchor>
      <docanchor file="SCOREP__MetricPlugins_8h" title="Optional variables">optionalV</docanchor>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_MetricTypes.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__MetricTypes_8h</filename>
    <class kind="struct">SCOREP_Metric_Properties</class>
    <class kind="struct">SCOREP_MetricTimeValuePair</class>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricBase</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a44a476f4e1ff9d8f010b2cad01fad08b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_BASE_BINARY</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a44a476f4e1ff9d8f010b2cad01fad08ba80effb7642d619f1ebe5a03553004a72</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_BASE_DECIMAL</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a44a476f4e1ff9d8f010b2cad01fad08ba60c93a26cb5239ffe9b4192b038f22b8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_METRIC_BASE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a44a476f4e1ff9d8f010b2cad01fad08ba2f56c515a03590389aacc4a8abaaa2bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricMode</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ACCUMULATED_START</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1a1523880fac41eb5f214655e551e8331c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ACCUMULATED_POINT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1a53d324f5a73bcdbe0b56f0305ee6f72d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ACCUMULATED_LAST</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1a155ba618cb2500d06962a4bd2977cca5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ACCUMULATED_NEXT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1aad196b4e1290ca2118da88a277732ee5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ABSOLUTE_POINT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1ab57b46315b7ae9d9da213f1bb0892530</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ABSOLUTE_LAST</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1a87945633571d47847896b0b8e4f520d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_ABSOLUTE_NEXT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1abe02d7ca978b2b6b2e68abef950296de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_RELATIVE_POINT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1a795e4bac81ba322b81c897899b7e7c29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_RELATIVE_LAST</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1a11f9de353156ce841d9d965f60e0e63b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_MODE_RELATIVE_NEXT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a27443ff10acf8b8aa54688ba3b4407c1aa2d6f44cbcb14de64aa82452ca62d5a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricPer</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>abfae3f6ae1b708da035525116e338245</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PER_THREAD</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>abfae3f6ae1b708da035525116e338245a4a79d82b45c7a256756e9d6dde0e51c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PER_PROCESS</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>abfae3f6ae1b708da035525116e338245ade5c4a019b657b981905237519e02fde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PER_HOST</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>abfae3f6ae1b708da035525116e338245a118a012081c7f1908c92410953bec33a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_ONCE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>abfae3f6ae1b708da035525116e338245ae4adc2bc72f27846350e75967a9dfac4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricProfilingType</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a5c0180d27e7a7861b2a8b24ced498ab6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PROFILING_TYPE_EXCLUSIVE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a5c0180d27e7a7861b2a8b24ced498ab6a6ff7d5353f60547d01eb0140729dae32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PROFILING_TYPE_INCLUSIVE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a5c0180d27e7a7861b2a8b24ced498ab6af1d335becd3735b0986eddf8ed3741a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PROFILING_TYPE_SIMPLE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a5c0180d27e7a7861b2a8b24ced498ab6ac0a2e32fa635ae077314d666efc1d77a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PROFILING_TYPE_MAX</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a5c0180d27e7a7861b2a8b24ced498ab6aba21587d84682c92f7249cb0460d4635</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_PROFILING_TYPE_MIN</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a5c0180d27e7a7861b2a8b24ced498ab6a9ba2a456fcd1080a011b577f1dca4162</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricSourceType</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_PAPI</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4a2fa4b248da0f479a28eb04c8bbda6ac8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_RUSAGE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4aab2a4e9e7592aea4ec361e5cc1bc0c9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_USER</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4a8f070d2bc3c58c50173108a81f4d1a7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_OTHER</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4acf8d21a2eba969d661813d8a7ff3c28a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_TASK</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4a2929e2e50528ebd619e94515a788edbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_PLUGIN</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4ab6c5192ea65ba9b5e75f6490c7d8e57a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SOURCE_TYPE_PERF</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a9819288f6647ff03ba1589a5853a05c4ab4e113900ff974dac0b6d2549acff9bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricSynchronicity</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ad198cb9c6534dacbcde6f042eace2341</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_STRICTLY_SYNC</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ad198cb9c6534dacbcde6f042eace2341ac4acad57bd5b2a240a15541222ac9d59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SYNC</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ad198cb9c6534dacbcde6f042eace2341aa5bf272316d91eaafe1664733da364ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_ASYNC_EVENT</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ad198cb9c6534dacbcde6f042eace2341ace115a7497931915d75d8afc71f52270</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_ASYNC</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ad198cb9c6534dacbcde6f042eace2341acb9358355339d8cbb1c0c8ab2dc56479</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricSynchronizationMode</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ab58c0207741a7f569fa79a2fe51cfb07</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SYNCHRONIZATION_MODE_BEGIN</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ab58c0207741a7f569fa79a2fe51cfb07a7cebcddcf52a7e18fcdb8bf6d1f59702</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SYNCHRONIZATION_MODE_BEGIN_MPP</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ab58c0207741a7f569fa79a2fe51cfb07aff352f9029057fe4f7682aa13837ba44</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SYNCHRONIZATION_MODE_END</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>ab58c0207741a7f569fa79a2fe51cfb07ade4688e8160b1a49246b7037e8283112</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricValueType</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a50126f1b0189d8b91d0dd07cdc02bbda</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_VALUE_INT64</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a50126f1b0189d8b91d0dd07cdc02bbdaa6e85992a0b697c98bafd0d45b5e80d9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_VALUE_UINT64</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a50126f1b0189d8b91d0dd07cdc02bbdaabf99f2109aef94657fe3c9eedec1ed95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_VALUE_DOUBLE</name>
      <anchorfile>SCOREP__MetricTypes_8h.html</anchorfile>
      <anchor>a50126f1b0189d8b91d0dd07cdc02bbdaa6bf160fff786c637c3c1e9778eee8fb0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_PublicHandles.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__PublicHandles_8h</filename>
    <includes id="SCOREP__PublicTypes_8h" name="SCOREP_PublicTypes.h" local="no" imported="no">scorep/SCOREP_PublicTypes.h</includes>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_HandleType</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_CALLING_CONTEXT</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809caa47f4f8eda2922781a9125d0cef489ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_GROUP</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca1424de5df0bb9867cc633d94f2d12277</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_INTERIM_COMMUNICATOR</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca1489336360d663fa7c7525d8b4ad8b7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_INTERRUPT_GENERATOR</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809cad06f37bbf3101c05ec900dca55a5f81a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_LOCATION</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca82ab1f06c6184efcccc77f0e6bf63ece</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_LOCATION_GROUP</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca1acf48953ab454f573219a3778d38e02</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_LOCATION_PROPERTY</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca42e331d4a4dd3bc82d5f4008b3826a8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_METRIC</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809cab5c93b112cb47ffe29ffe63e33f1c423</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_PARADIGM</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca7d5e413d3ae9d2dd4e2b08dc36b091bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_PARAMETER</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca1369439d8d6218977cdc120373939a77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_REGION</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca5eb1ffd94c087b990cc1a7ead1cd928c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_RMA_WINDOW</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809cac4835213f3cf14f59d67f161a625ca50</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_SAMPLING_SET</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca1fca5eef4e5d524d4251cef0d2bc1412</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_SAMPLING_SET_RECORDER</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca0a9f6949728cf82fd71bc29f8d910242</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_SOURCE_CODE_LOCATION</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809cad38dda216681b1f89f1851a385ae8de9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_SOURCE_FILE</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca61ba5c38e7a523c739f44e7ba32a7cc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_STRING</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca6c6fdc436061ba34530bd9fe420bc854</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_SYSTEM_TREE_NODE</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809caf06f7b2e3430b4623c44b022f1564494</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_SYSTEM_TREE_NODE_PROPERTY</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca3d0b5c957cbb23389d57dedd862fe28f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_CARTESIAN_TOPOLOGY</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca890343bf2108c65eeae721a2c3edbe26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_CARTESIAN_COORDS</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca871b1150e20de164806077bf979ed688</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_IO_FILE</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809cad501e5d6d1d8c90e6606666e3ed3d06d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_IO_FILE_PROPERTY</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809caf21eeb8b2020b7c68985bd7020ba43b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_IO_HANDLE</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca16b782fddad4c5d00b539fef6ec3e936</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_IO_PARADIGM</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809cabcfc53a8885a992bc00f56fe3fbd09cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_HANDLE_TYPE_NUM_HANDLES</name>
      <anchorfile>SCOREP__PublicHandles_8h.html</anchorfile>
      <anchor>a8f44de28d8df3e0cbf9314666ec0809ca0bd7ec52b48a0c16fdb648518687c280</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_PublicTypes.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__PublicTypes_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_ALL_TARGET_RANKS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gadcedcc15f54c90fed84776b728c7427e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_EXIT_STATUS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gab3efa3ee03b9ea19f50cedb20f505c46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_LINE_NO</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa902c1f27bc699a3177efbe6cecc7264</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_METRIC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga7f927936deaeb989b4ea038a1ef9745d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_PARADIGM</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga4aa85f3b492f91edf67ef0b0aeb3870e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_REGION</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gabfb6015f4987baa2f1d3b4965fbb1027</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_ROOT_RANK</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga43f526b8899d65da08ca24e556f12080</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_SAMPLING_SET</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga00bb9822a4acd564158c741ff9f67b78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_SOURCE_FILE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gab7bfb29a1590fa3d0ee63ad002eb5b23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_LOCATION_TYPES</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaac8240c4c70b7b8aee9d63d0a138c75c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_MOVABLE_NULL</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga416820d06bb171c07dbb66010862ffc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>SCOREP_Allocator_MovableMemory</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga073a5d370b1bcdf739df1e75380a03b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_Allocator_MovableMemory</type>
      <name>SCOREP_AnyHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa674d5e3722f8c9b7c1d23a475603365</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int64_t</type>
      <name>SCOREP_ExitStatus</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gad8d146ff25ac3d3e8baa8f9103db2ca9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>SCOREP_LineNo</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga1dcf04ed0004756cabd415fba210750a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_MetricHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga4faa73ab360d2a1c5bc278ed49669e64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>SCOREP_MpiRank</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga3c9d908fb280602e92791134cfb57e01</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t</type>
      <name>SCOREP_MpiRequestId</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga5f47cddd80bc28f7c01c2192334c4d96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_ParadigmHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gab5dfdc503fa5ae4cd5c1545d2e9f8855</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_RegionHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga35c3f5ba0398e83f528b4241c8002c06</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_SamplingSetHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga244d2bfaa62f4d1fd13fa7ab5d16218a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_SourceFileHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga9c28c3cffcfd47763efd1607dd63f767</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct SCOREP_Task *</type>
      <name>SCOREP_TaskHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gad6073c055f49446ef7e60e7ee95a91a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_CollectiveType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga31673b3012520b84dfc10cf9d2e50032</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_BARRIER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aa26c04527ba802ed1e683ae26b94d13f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_BROADCAST</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a6c81cef42738c5fe52a40a697e2f2ec0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_GATHER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a3ca2c5ed3773a8b5330fca73b3a0517a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_GATHERV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a36d8b3c66563d98bb65986eb6dd481a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_SCATTER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a602dfd1852c7a8550be71a364cf72796</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_SCATTERV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a5fe5314366351990bed93a8f03f340ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLGATHER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032ad183ed1e931a746fadccf6bcbe95cbea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLGATHERV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aed0135d39789398c88c323a995703328</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLTOALL</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a8562667889a5a8dd1b1bdbbd437aec79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLTOALLV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aa2092bb78bd8676afdbaa01ef6bea213</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLTOALLW</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032abe6565488decc2cdd9b0ef68c6c9f455</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLREDUCE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032afcfd8c6abb8206f1cb7ff41322c705b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_REDUCE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aa7591423702cab3c95246dad2711c542</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_REDUCE_SCATTER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032afe4d3f5084a8eb696700f4723851f775</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_REDUCE_SCATTER_BLOCK</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a0a3da23b2e9716470a28a504dffbc41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_SCAN</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a2d11789b83703e2b49dc1b786fa00006</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_EXSCAN</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a6e9507c9ef3f90d11cd638d650b475e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_CREATE_HANDLE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a74e51c164e843d05299b56b4fcc734a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_DESTROY_HANDLE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aca01f3589fe5f36bd5dc374195a9fec6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032addd31856975f3d2a9ab9f583aa567303</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_DEALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a29e3488193957364351940cd63091fba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_CREATE_HANDLE_AND_ALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a59cf430980bcd543835508a09342322e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_DESTROY_HANDLE_AND_DEALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a0e0602af785147df980f7f5e69e104d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoAccessMode</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga3aea792cd0d6e5a675ba9819fa71282a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aad84b6b2de05da72ec3be0d920c9c4d89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_READ_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aa801952fc2320b38adf386c46ccea1805</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_WRITE_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aafb29c9c6505ff890bc32405fd04af53c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_READ_WRITE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aa077a947e8f08f2624f4bd21209c2613f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_EXECUTE_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aaf2e9988b6f16bae045bd56460be910fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_SEARCH_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aadf10faee7fa11a3cf2a8eb98a910ec4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoCreationFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga2b0045dcee30b266b986c6dad60ce94d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dad0b101a848e6aa802732371126784ea9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_CREATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dada19c77b3726769e981c14ce73b42073</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_TRUNCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da7d9be856ea196c350943eeda3dd90235</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_DIRECTORY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da389eb43db1302bfc9e3f3954e71ba09a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_EXCLUSIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da8a59f6f509bb17743586727860a11ece</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NO_CONTROLLING_TERMINAL</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dac403f7fb601cff2bb547d273c5656f48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NO_FOLLOW</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da9fd3144d339a47dce06f8ed10c362067</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_PATH</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da44f5040ed948f419535ad63666bc2043</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_TEMPORARY_FILE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dafd76b21e02eda8cc023e66bdd45e6fd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_LARGEFILE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da2b17a70d56ead493b62cc3d99313d403</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NO_SEEK</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da403da02c9259e5c88f5a5feb18a3b89a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_UNIQUE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dab5ee7b6d5ae02998f1dab2067d9539cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoOperationFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga83f3e78d8bd291fb70de8d849d4bd2f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9aa2d790e5c24464ad10b9655641a133a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_BLOCKING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9a8d1dd38f75dfddbbe3a27ba447543089</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_NON_BLOCKING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9a095fd84ee82d81df647c7a2616df108d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_COLLECTIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9aac53afded8a6cdcf3d022c4604153724</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_NON_COLLECTIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9aa55839e696b8e426c1cb445974965c95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoOperationMode</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga3981a3958c6fe3ccab5acafbf7ad29ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_MODE_READ</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3981a3958c6fe3ccab5acafbf7ad29baa91656cd813fc67ee198288a3c3735cbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_MODE_WRITE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3981a3958c6fe3ccab5acafbf7ad29baafbd448d4186af6dadf8658834f5e7efe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_MODE_FLUSH</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3981a3958c6fe3ccab5acafbf7ad29baa14354fd9fc6cfd6bf27900529652ae49</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoParadigmType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga8a40e0b4ac99eb2434183edb26a6807d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoSeekOption</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga8815c891a0fc20fca86f5c4a674b8c59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_FROM_START</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59ac37ebe46277c781aa5aa167b4dfde708</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_FROM_CURRENT</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59adaee654423132182f27e6e419add25a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_FROM_END</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59aeaeb74103c7f015f1b56b2fe3a9b6dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_DATA</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59af7a5a09492ce37f475901d0553537968</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_HOLE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59a09785f685343a03054812a8ace7bce89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_INVALID</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59aff649939b6f3259e8d2bbc2ec48ecbe0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoStatusFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga4d9ed0834a9c13b22aa737288cd8b184</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a24058cd8e998ea9329603584dea0f45e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_CLOSE_ON_EXEC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184ac6b2c84635cc1fbf69bd3e65020ed69f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_APPEND</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a58e92afe762426714c8d05271faac3a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_NON_BLOCKING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a64de3b345d7f0dd4fae25e9de32f3ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_ASYNC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a4ad14d9f9ca305196914ceb458715fdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_SYNC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a68c7e9ba02d1823efa9e0081e2d03b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_DATA_SYNC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a0e54a49c0256df0930a8d1c69614c4a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_AVOID_CACHING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a611cc98ffdae579551919ae49aa06fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_NO_ACCESS_TIME</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184ac7f64e103488476b07e18c5336399090</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_DELETE_ON_CLOSE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a74764896a436bd5feed5deb293d42cf6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Ipc_Datatype</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga6eec6de9cc89e48af2be1035b0155899</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Ipc_Operation</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa61cd8bcd44b6cc89cc33ae16c8da992</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_LocationType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa9e2e42350b85c45c06a32ccf8cdf5d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_LOCATION_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggaa9e2e42350b85c45c06a32ccf8cdf5d4a00c13fa42490847d45ac4a91140a895c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_LockType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga13e99a7883e8e4d3468320f3fae14887</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_LOCK_EXCLUSIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga13e99a7883e8e4d3468320f3fae14887a37a94628310f7f083dee77a253a4f1a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_LOCK_SHARED</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga13e99a7883e8e4d3468320f3fae14887a6e12d4fea638280cb3b7d0a1de7d21e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_LOCK_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga13e99a7883e8e4d3468320f3fae14887a82790f80b798a36195230de5bd0b8728</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricOccurrence</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga6e2f8848981c6264b999fe925488a516</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_OCCURRENCE_SYNCHRONOUS_STRICT</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a660126448f2b715915a832b1cc87fdaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_OCCURRENCE_SYNCHRONOUS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a767362f2cfb151b03f24db2e86c5d783</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_OCCURRENCE_ASYNCHRONOUS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a333e3e8749f4f63359fa1467ed3346fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_METRIC_OCCURRENCE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a45cdc4cb56534925c0fef4cc5ffc82e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricScope</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gabc0b01d887d84683fca8bd5aface6ae4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_LOCATION</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a12c4fa145873068939247b08c260c23e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_LOCATION_GROUP</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a060e44dad9b1d52ec44a04306e8e1028</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_SYSTEM_TREE_NODE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a114a3d49db709d47368ed7ee0c1871dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_GROUP</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a94d0841c12dc62bb71eb2111f0eeecda</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_METRIC_SCOPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a9dad2506696b26ae8ce99e70e94efa25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_ParadigmClass</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga215b57f4b6077f5b49cf4d07789426fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_PARADIGM_CLASS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga215b57f4b6077f5b49cf4d07789426faac74f1dedc00de6a3b3033fe717c4141d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_ParadigmType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga54ea902852bed473f674ed1f9cc8e523</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_PARADIGM_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga54ea902852bed473f674ed1f9cc8e523a3b1802b3adbb923310cb178edb467ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_ParameterType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gad5610b49b0b12b5d3f6c0c4a09924afd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_PARAMETER_INT64</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afda4ed26dbfa2eef7a8502448210f3756da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_PARAMETER_UINT64</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afda437b58e6aece0c9e5209b35ab0068f65</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_PARAMETER_STRING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afdaf77db7854e898dce09f54d24c733bc26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_PARAMETER_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afda2a1034f6b346c65658a69e725051319e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RegionType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaeb4e4c2fbdfe182a263c8d9d41aa0ffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_REGION_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggaeb4e4c2fbdfe182a263c8d9d41aa0ffbae8e6e39a524dd4df1138ca3c9586cccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RmaAtomicType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gada9d37396e7a2b09f87f148f08eb620c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RmaSyncLevel</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gadf190946dbad8ff7875f457f808bc90b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RmaSyncType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gabe2ec192d5ad0f1971942ba25600e69f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_RMA_SYNC_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabe2ec192d5ad0f1971942ba25600e69fa22a6a1719aeb48521652df5088ca0e7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_SamplingSetClass</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gacae06b5b045fb7175c1f3ac5913893ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SAMPLING_SET_ABSTRACT</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggacae06b5b045fb7175c1f3ac5913893acae4f602754ddbfedb1e9c93260d242ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SAMPLING_SET_CPU</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggacae06b5b045fb7175c1f3ac5913893aca083dcef173720235a73a5fac13bf3c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SAMPLING_SET_GPU</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggacae06b5b045fb7175c1f3ac5913893aca7c722818bfb090c58837db11e4172ec1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Substrates_RequirementFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gac35cca5dd67124a45c915f041a48d3b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_REQUIREMENT_CREATE_EXPERIMENT_DIRECTORY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0a03f8f9a89733007a2a2a261f26d445de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_REQUIREMENT_PREVENT_ASYNC_METRICS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0a30a12a82fc69fa9f9f5de52a2a5a19e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_REQUIREMENT_PREVENT_PER_HOST_AND_ONCE_METRICS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0ab5962b10ff54123ab15e74aa39e9b9fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_NUM_REQUIREMENTS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0a2338406af0ddac42535a3f141edf16cb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_SubstrateEvents.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__SubstrateEvents_8h</filename>
    <includes id="SCOREP__MetricTypes_8h" name="SCOREP_MetricTypes.h" local="no" imported="no">scorep/SCOREP_MetricTypes.h</includes>
    <includes id="SCOREP__PublicTypes_8h" name="SCOREP_PublicTypes.h" local="no" imported="no">scorep/SCOREP_PublicTypes.h</includes>
    <includes id="SCOREP__PublicHandles_8h" name="SCOREP_PublicHandles.h" local="no" imported="no">scorep/SCOREP_PublicHandles.h</includes>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_Callback</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a61889ba100d69b5770e0764991b30d53</anchor>
      <arglist>)(void)</arglist>
      <docanchor file="SCOREP__SubstrateEvents_8h" title="Advice">advice_substrate_events</docanchor>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_CallingContextEnterCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a528345f184182a0c76af480a2d4757d7</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_CallingContextHandle callingContext, SCOREP_CallingContextHandle previousCallingContext, uint32_t unwindDistance, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_CallingContextExitCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a3bf0ebc1d3eab7fcf9824c55f587a10f</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_CallingContextHandle callingContext, SCOREP_CallingContextHandle previousCallingContext, uint32_t unwindDistance, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_DisableRecordingCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a53ada647f3ce81ff765e6f496cc14b1f</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_EnableRecordingCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1b8aa3291291f37bd27317ec262fcc70</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_EnterRegionCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a7cf654f2a84c3a625592ef7fd0a4900c</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_EnterRewindRegionCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a0262efa56c90f8b8ae24e4d9cd30179f</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ExitRegionCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>adafeab74a084b290a74c1157f01ad953</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ExitRewindRegionCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ac2daf7dd2db9bcd1370fcc3f61608cb4</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, bool doRewind)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoChangeStatusFlagsCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ab642cc4516a41e6c2368f6245fa12a34</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, SCOREP_IoStatusFlag statusFlags)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoCreateHandleCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a561c6580975a37a274b487a2afaf4e2b</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, SCOREP_IoAccessMode mode, SCOREP_IoCreationFlag creationFlags, SCOREP_IoStatusFlag statusFlags)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoDeleteFileCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ae4b17b59b4e0b8489f8963b9694b045a</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoParadigmType ioParadigm, SCOREP_IoFileHandle ioFile)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoDestroyHandleCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aadf20e5f557b5bb9b16a404be52e1ecb</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoDuplicateHandleCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a3b3fa2c0f0e6f8a541d4b1e36ac95285</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle oldHandle, SCOREP_IoHandleHandle newHandle, SCOREP_IoStatusFlag statusFlags)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoOperationBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1eb0165ea050a637a66087007d512a27</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, SCOREP_IoOperationMode mode, SCOREP_IoOperationFlag operationFlags, uint64_t bytesRequest, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoOperationCancelledCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a9a8cbaed94213c75e5f4ac5c1d4557bd</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoOperationCompleteCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>af648b297361c4680d621d9ce4c5d795c</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, SCOREP_IoOperationMode mode, uint64_t bytesResult, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoOperationIssuedCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>adfed1517349db51700a855159b8f9cf5</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoOperationTestCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>afa8bac08f71d3f950f206d9271395fbd</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoSeekCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a005fcb0482794b292aee1bb18f74bb2e</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, int64_t offsetRequest, SCOREP_IoSeekOption whence, uint64_t offsetResult)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiCollectiveBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a77b8403262e0a200a1f0d07366c42eef</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiCollectiveEndCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ac21eb12748b6b48aee92ec4009530b4a</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_InterimCommunicatorHandle communicatorHandle, SCOREP_MpiRank rootRank, SCOREP_CollectiveType collectiveType, uint64_t bytesSent, uint64_t bytesReceived)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiIrecvCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aafb5cefd57aec87ee7f7783a7fc7a102</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRank sourceRank, SCOREP_InterimCommunicatorHandle communicatorHandle, uint32_t tag, uint64_t bytesReceived, SCOREP_MpiRequestId requestId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiIrecvRequestCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ad7b91de97205b9cf4c96d9b3187123f7</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRequestId requestId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiIsendCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a4dc9ed892573ce28e76336a2fcd0c38a</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRank destinationRank, SCOREP_InterimCommunicatorHandle communicatorHandle, uint32_t tag, uint64_t bytesSent, SCOREP_MpiRequestId requestId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiIsendCompleteCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a425f47b01fccb74a3bf8c6ac340b2d10</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRequestId requestId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiRecvCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a9f483e69bd5790042b5babe81c021442</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRank sourceRank, SCOREP_InterimCommunicatorHandle communicatorHandle, uint32_t tag, uint64_t bytesReceived)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiRequestCancelledCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a9376fb54c71f336c432a48993ce99c6d</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRequestId requestId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiRequestTestedCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>af7bf6922fb8d0c9c66f023c063d720ae</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRequestId requestId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_MpiSendCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a21d6afbf5dc8c3515bd0e882b1a33100</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_MpiRank destinationRank, SCOREP_InterimCommunicatorHandle communicatorHandle, uint32_t tag, uint64_t bytesSent)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_OnTracingBufferFlushBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a172af989344c05457bd243aec960aaeb</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_OnTracingBufferFlushEndCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a5c9174ba0b81c0e4fdffbfb7e0227146</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaAcquireLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ae4dcec7228bfd86f43b6c14223fd3261</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, uint64_t lockId, SCOREP_LockType lockType)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaAtomicCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a7d1f7e6d3b760542b4fc5e08265fa368</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, SCOREP_RmaAtomicType type, uint64_t bytesSent, uint64_t bytesReceived, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaCollectiveBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a9763ffeca6f934fad9a2d3181a4408ad</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaCollectiveEndCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ad26a162e88aed5fdf2781dbf35de64c5</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_CollectiveType collectiveOp, SCOREP_RmaSyncLevel syncLevel, SCOREP_RmaWindowHandle windowHandle, uint32_t root, uint64_t bytesSent, uint64_t bytesReceived)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaGroupSyncCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a79f603d1f649307cddda788c340ba3ba</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaSyncLevel syncLevel, SCOREP_RmaWindowHandle windowHandle, SCOREP_GroupHandle groupHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaOpCompleteRemoteCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a61aee6553a3cbbf7fa59c2a47b2050e4</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaOpTestCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ad7b4cadca7465e00246de820b771279d</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaReleaseLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a323bf071c0ff144a16d1738155542509</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, uint64_t lockId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaRequestLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a11ab2447cb326dafc6e67fad9ad555a9</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, uint64_t lockId, SCOREP_LockType lockType)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaSyncCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>acc604d7abbb5d0c86c87f94221e11cca</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, SCOREP_RmaSyncType syncType)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaTryLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1c4d6a3a95c6640cca8286a24a7e756c</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, uint64_t lockId, SCOREP_LockType lockType)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaWaitChangeCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a418845f2d55b0c4c7d544de8397f55e2</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaWinCreateCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a52730e0044bbd16dd011031f0a44029a</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaWinDestroyCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ae2e5612fd226d96f34a62934aa1d9412</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_SampleCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ab3b3eacc974f2310e14f3dc686f870ab</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_CallingContextHandle callingContext, SCOREP_CallingContextHandle previousCallingContext, uint32_t unwindDistance, SCOREP_InterruptGeneratorHandle interruptGeneratorHandle, uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinForkCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ab77d939ee4542d65c106746e91613495</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, uint32_t nRequestedThreads, uint32_t forkSequenceCount)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinJoinCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aafd3cb1dbea7c336d0ae43af301279d9</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinTaskCreateCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a3bf6a6c79bf3f4b93133fa2b0266b06b</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam, uint32_t threadId, uint32_t generationNumber)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinTaskSwitchCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a59371eb9abe061605a877119765e0cd7</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, uint64_t *metricValues, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam, uint32_t threadId, uint32_t generationNumber, SCOREP_TaskHandle taskHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TrackAllocCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa699d4ab480fedff2a249bad55de7b77</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, uint64_t addrAllocated, size_t bytesAllocated, void *substrateData[], size_t bytesAllocatedMetric, size_t bytesAllocatedProcess)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TrackFreeCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>af7f38c3806988090bb7ad05c8dfbf717</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, uint64_t addrFreed, size_t bytesFreed, void *substrateData[], size_t bytesAllocatedMetric, size_t bytesAllocatedProcess)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TrackReallocCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a774d9815aea1342a07345a5d3436c9d9</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, uint64_t oldAddr, size_t oldBytesAllocated, void *oldSubstrateData[], uint64_t newAddr, size_t newBytesAllocated, void *newSubstrateData[], size_t bytesAllocatedMetric, size_t bytesAllocatedProcess)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TriggerParameterStringCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a8acfa4272993a6f149179e7276da07ea</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParameterHandle parameterHandle, SCOREP_StringHandle string_handle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_WriteMetricsCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>af3a5244916c45b8048d783dc9d34062f</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_SamplingSetHandle samplingSet, const uint64_t *metricValues)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaPutCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa6ce3be65c43a2473b4baf4355990dfa</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, uint64_t bytes, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaOpCompleteBlockingCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a87660dfa16b1b8c938caece6a037ba84</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadAcquireLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a02272d75c99acf86d7e7cded336fd532</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, uint32_t lockId, uint32_t acquisitionOrder)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TriggerCounterInt64Cb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a87dbed101863759d653a077fd6bc8826</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_SamplingSetHandle counterHandle, int64_t value)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TriggerParameterInt64Cb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1c45c7729d42e23f0469704d1347ca92</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParameterHandle parameterHandle, int64_t value)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinTeamBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a23546b2a8507243629418d2c6468adc6</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinTaskBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a903016904207487a0e929e144e174992</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam, uint32_t threadId, uint32_t generationNumber, SCOREP_TaskHandle taskHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadCreateWaitCreateCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1845c54dfe86819b042cec111d589c26</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam, uint32_t createSequenceCount)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoAcquireLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ac7bea1e0223c961cebf882268d2e0681</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, SCOREP_LockType lockType)</arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Substrates_EventType</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_ENABLE_RECORDING</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea8b61373d1e4d5a6ecc60cff8327b844a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_DISABLE_RECORDING</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeafca85b2f92aeb9a868a26252392efeaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_ON_TRACING_BUFFER_FLUSH_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea882cbe37633537e8c0feee92937f42d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_ON_TRACING_BUFFER_FLUSH_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea929008f21f0549062a05e7eba5e0a8db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_ENTER_REGION</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea2675e09c14f47db50bc0b5031719a43b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_EXIT_REGION</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeada67ee968452c68c743e4f69f3c304e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_SAMPLE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea92ca39e80145f651525b9373e1ad62e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_CALLING_CONTEXT_ENTER</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aead963989066a3f06630f3c2c7096985a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_CALLING_CONTEXT_EXIT</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaf85975c73d2bb3609cc3fa1ed20abf6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_ENTER_REWIND_REGION</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea1be242bcbc182783d35e050c40b1dda7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_EXIT_REWIND_REGION</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea168d4329cc5d8da14c4f7743b6ab2bff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_SEND</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaa8e99024531ad3057267ec38e063169c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_RECV</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea4c44b3e8700d674a5cf1450d574e33e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_COLLECTIVE_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea90b70256e9432da02e160a36c148bc4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_COLLECTIVE_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea18ebdc3dcdc24eaef86680943a601359</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_ISEND_COMPLETE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeacdf6430563795780aca82d0a0150e964</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_IRECV_REQUEST</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea755d2cc2ffe506121dbb5fecaa2c6a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_REQUEST_TESTED</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea35a653263e8b95dc81b5614861bb9d0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_REQUEST_CANCELLED</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea58d0dc851e37306a89cd779bb67f8343</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_ISEND</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea51377139624d10dfd5c415edeb5d9862</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_MPI_IRECV</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaebba935642b9b2a83fd4aaaf0dd070aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_WIN_CREATE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaf4694477f7bbf8af95224d94d030ee4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_WIN_DESTROY</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaf12cd469a72502637a23669ec59f6000</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_COLLECTIVE_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea57baf288e7c304c44a4dcd3f2231acd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_COLLECTIVE_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea64cb7ee36e76377b35c5104527b38a8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_TRY_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea736d3a3c725af7631d6f7a10f460c99f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_ACQUIRE_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea9af3f37a91aecd521b82127cd219201b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_REQUEST_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea656abdc694e77552dcba924e7a7a8d9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_RELEASE_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea3f857bd370a01d9fc1a23c3245146a1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_SYNC</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea14f2e811ce8fae395a9b668ecbfd9ec1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_GROUP_SYNC</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaebe974b2d21cf5deb5b22ecb799fde80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_PUT</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeadd31449f80ff933f12c7cd08831fa2cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_GET</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea66fd065bcf75455b77730328cf415b47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_ATOMIC</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea557ced5b82f4bb99d3568b459666437a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_WAIT_CHANGE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea0e0ed9421df94a473bfbdc39c4eab69b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_OP_COMPLETE_BLOCKING</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea50c963a170d6064ea07d38f256e49ce9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_OP_COMPLETE_NON_BLOCKING</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea9ac3863cc94bccea01fbf618aecf9185</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_OP_TEST</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaeec2eadcc943be83a11c3dee3cdb11c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_RMA_OP_COMPLETE_REMOTE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea44bb6caefc01539ac1e99fcccbeac048</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_ACQUIRE_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea04270752df2821ad5e158deb3e5391dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_RELEASE_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea1a7878419dd24abb3bba97d87e01ac4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRIGGER_COUNTER_INT64</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea2b6f40885ce751779c34397ea078b9da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRIGGER_COUNTER_UINT64</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea7f4b021a3b9c27b01bcb771102fe7e3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRIGGER_COUNTER_DOUBLE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea0d81b2f375bedd9cf59883b8b10d13eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRIGGER_PARAMETER_INT64</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea14ee8f9c72f0d8013e1607d9a1e77373</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRIGGER_PARAMETER_UINT64</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea76376378c2393ba7c32e9d7e21c570b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRIGGER_PARAMETER_STRING</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea5ff59f025727f852c1c62d998802c71e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_FORK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aead6f3dd9a96799a084bcf5d0b266e0791</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_JOIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea8931b8492ce6192f4e046ca2310c889b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_TEAM_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea388eab5106b6da4fdb4b149a8771c255</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_TEAM_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeae13e329a998668fe16c0ae6334a8414f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_TASK_CREATE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaa4c9939b3ef6bbc88c385b231647bac4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_TASK_SWITCH</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea3f2616b0223badcb3fae4f074a52aba5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_TASK_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea24d162b08ff2debce60bd215dce084ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_FORK_JOIN_TASK_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaecb1c053b558b559f5c6d85458c91caa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_CREATE_WAIT_CREATE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea154b4c8472f70327974157b6256b12a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_CREATE_WAIT_WAIT</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaa8adbd09ba80f9f01b67d47fad624295</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_CREATE_WAIT_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea4444849c20739a16d3cbd50eface038e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_THREAD_CREATE_WAIT_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea7817ffd943b45a5106cc481ee263692a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRACK_ALLOC</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea2dcd1f9543b9ede1c9442dd83043c000</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRACK_REALLOC</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea3e0f68c9c8cd375a52106f60f90b8059</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_TRACK_FREE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aead715e796f71bea4fb03b1c244a838e3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_WRITE_POST_MORTEM_METRICS</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaa889bd59ae080d66732940e3eba8b77f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_PROGRAM_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea618ebadae9616e58e0eb82b9859360cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_PROGRAM_END</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaad8c89e952718c1a7bbe8d612ab1afa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_CREATE_HANDLE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea5e24ce9c6eba974ae3a9cff803e6d2bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_DESTROY_HANDLE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaa7662f831f04da0609a24ae77125f5a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_DUPLICATE_HANDLE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea5e5c20dd72cf2a9b8061bc65bb7361d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_SEEK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaa68eba60a387eddfa7cc054a30bd632a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_CHANGE_STATUS_FLAGS</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea38ed35fa8444833b9cbda7b37166318d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_DELETE_FILE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeae348eb760b10dae48d60b5ed85ababf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_OPERATION_BEGIN</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeafad51334b9033a745b4db9b3b5e31a08</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_OPERATION_ISSUED</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea5ef73bb10a7046e7bac14afeb646114d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_OPERATION_TEST</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea81b934f2b4961a9c8ff676422e32db92</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_OPERATION_COMPLETE</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeaaa39add08abd4cd48590f4126439f863</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_OPERATION_CANCELLED</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeac9fc291b3dfcc7f8c630b31a17c4cbd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_ACQUIRE_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeac0f949987283e0e1254fb35bc889a33e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_RELEASE_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea8061f1e9132ca7e5f840a97da772dd29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_EVENT_IO_TRY_LOCK</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aeac8b26fb665ba78f8eb0d004ed2a8932b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_NUM_EVENTS</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a575d520bd98b8dfa5d4decc1bf6233aea11828b418beefffb7431428237edab72</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Substrates_Mode</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa1216c0442a344ac2d9d72a45660e656</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_RECORDING_ENABLED</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa1216c0442a344ac2d9d72a45660e656a2dfd6badc622bed45e4adad371c82187</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_RECORDING_DISABLED</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa1216c0442a344ac2d9d72a45660e656aa23212ac32425a3227fe047bd84352cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_NUM_MODES</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa1216c0442a344ac2d9d72a45660e656a5eebba78c46842fc8a8d8b8f8b249533</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaPutCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>aa6ce3be65c43a2473b4baf4355990dfa</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint32_t remote, uint64_t bytes, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_RmaOpCompleteBlockingCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a87660dfa16b1b8c938caece6a037ba84</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RmaWindowHandle windowHandle, uint64_t matchingId)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadAcquireLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a02272d75c99acf86d7e7cded336fd532</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, uint32_t lockId, uint32_t acquisitionOrder)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TriggerCounterInt64Cb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a87dbed101863759d653a077fd6bc8826</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_SamplingSetHandle counterHandle, int64_t value)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_TriggerParameterInt64Cb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1c45c7729d42e23f0469704d1347ca92</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParameterHandle parameterHandle, int64_t value)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinTeamBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a23546b2a8507243629418d2c6468adc6</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadForkJoinTaskBeginCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a903016904207487a0e929e144e174992</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_RegionHandle regionHandle, uint64_t *metricValues, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam, uint32_t threadId, uint32_t generationNumber, SCOREP_TaskHandle taskHandle)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_ThreadCreateWaitCreateCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>a1845c54dfe86819b042cec111d589c26</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_ParadigmType paradigm, SCOREP_InterimCommunicatorHandle threadTeam, uint32_t createSequenceCount)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>SCOREP_Substrates_IoAcquireLockCb</name>
      <anchorfile>SCOREP__SubstrateEvents_8h.html</anchorfile>
      <anchor>ac7bea1e0223c961cebf882268d2e0681</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_IoHandleHandle handle, SCOREP_LockType lockType)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_SubstratePlugins.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__SubstratePlugins_8h</filename>
    <includes id="SCOREP__PublicTypes_8h" name="SCOREP_PublicTypes.h" local="no" imported="no">scorep/SCOREP_PublicTypes.h</includes>
    <includes id="SCOREP__PublicHandles_8h" name="SCOREP_PublicHandles.h" local="no" imported="no">scorep/SCOREP_PublicHandles.h</includes>
    <includes id="SCOREP__SubstrateEvents_8h" name="SCOREP_SubstrateEvents.h" local="no" imported="no">scorep/SCOREP_SubstrateEvents.h</includes>
    <class kind="struct">SCOREP_SubstratePluginCallbacks</class>
    <class kind="struct">SCOREP_SubstratePluginInfo</class>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_SUBSTRATE_PLUGIN_ENTRY</name>
      <anchorfile>SCOREP__SubstratePlugins_8h.html</anchorfile>
      <anchor>ac9e26aec6387984b9bb3b2490f1356ec</anchor>
      <arglist>(_name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_SUBSTRATE_PLUGIN_UNDEFINED_MANAGEMENT_FUNCTIONS</name>
      <anchorfile>SCOREP__SubstratePlugins_8h.html</anchorfile>
      <anchor>a10b3bb0f58bfa8bb95822c4b3357e476</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_SUBSTRATE_PLUGIN_VERSION</name>
      <anchorfile>SCOREP__SubstratePlugins_8h.html</anchorfile>
      <anchor>a7d1bbc495c8dfe980c64e2e10d97cba6</anchor>
      <arglist></arglist>
      <docanchor file="SCOREP__SubstratePlugins_8h" title="Advice for developers">advice_substrate_plugins</docanchor>
      <docanchor file="SCOREP__SubstratePlugins_8h" title="Functions">funcs</docanchor>
      <docanchor file="SCOREP__SubstratePlugins_8h" title="Mandatory variable">variables</docanchor>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_User.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__User_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga23e865fc48814d8f1a73f2138a69c749</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_OA_PHASE_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga40f15c9d9ab7069a6b2e86ab016f6c8b</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_OA_PHASE_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gadc3d51e99a65b4094ce8d14be406c713</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8fff2e6053e2a36a4c3421e8114a912e</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_ENTER</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8c8f772145f95dce57dcf86b6998365c</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaab4b3ccc2b169320c1d3bf7fe19165f9</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gad481ce21b169390edb4cf6d206359672</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga36bc4808f2cbdfd75f9a05d2124698d1</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga6cd32d0be80a23887723f728a6a9d0eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaf86321e31c824a10c9907e9961052f88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_GLOBAL_REGION_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga7019f070cfc0ff854e701a9aeb9e8988</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_GLOBAL_REGION_EXTERNAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaf0c9dfaad79f9844fe0cb2464763bb65</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gad4d135ed8a7f81100125658cd402d78e</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga08175aaf74cc890748fdd8d858e7f993</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_STRING</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga4cf20238efa2cfa9098c52d71921430a</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_LOCAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga5ff73525b7503a91cebfadabd347af50</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_GLOBAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8aec5246b3ffd6d5ed8cd33fef73932f</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_EXTERNAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga1f457747020689dd37f02977132805e4</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaabf4d21272e8abbfab5db78a1f932687</anchor>
      <arglist>(metricHandle, name, unit, type, context)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gac4808a743c67e6f1284dce290695ecff</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gae56cb2e66065f563f0b7ab030c17c538</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_DOUBLE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga31e598aa18b69054fcdfb28e0032fad0</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_CREATE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaaaf62bc0ce216cac48c788919735d9c3</anchor>
      <arglist>(userTopology, name, nDims)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_ADD_DIM</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga614e23fb934641599a9d1592b81201fa</anchor>
      <arglist>(userTopology, size, periodic, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga1301cb8d825c425c9ae16d94299a08f3</anchor>
      <arglist>(userTopology)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_SET_COORDS</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gafccee35576f4754cb05b51cfd2583c3c</anchor>
      <arglist>(userTopology, nDims,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gab5b2732699c4885ed7052b66a8c41383</anchor>
      <arglist>(userTopology)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga20640122ace776d083a163fd86fb46f9</anchor>
      <arglist>(name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_ON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga4a74d67519387ca834adbd6661afa818</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_OFF</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gafa31b2ab267a4997f7b62bcc38ed5ac9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_IS_ON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaa477c37a05e90ed79d1d7ae9c1b9a691</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga23e865fc48814d8f1a73f2138a69c749</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_OA_PHASE_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga40f15c9d9ab7069a6b2e86ab016f6c8b</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_OA_PHASE_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gadc3d51e99a65b4094ce8d14be406c713</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8fff2e6053e2a36a4c3421e8114a912e</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_ENTER</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8c8f772145f95dce57dcf86b6998365c</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaab4b3ccc2b169320c1d3bf7fe19165f9</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gad481ce21b169390edb4cf6d206359672</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga36bc4808f2cbdfd75f9a05d2124698d1</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga6cd32d0be80a23887723f728a6a9d0eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaf86321e31c824a10c9907e9961052f88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_GLOBAL_REGION_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga7019f070cfc0ff854e701a9aeb9e8988</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_GLOBAL_REGION_EXTERNAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaf0c9dfaad79f9844fe0cb2464763bb65</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gad4d135ed8a7f81100125658cd402d78e</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga08175aaf74cc890748fdd8d858e7f993</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_STRING</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga4cf20238efa2cfa9098c52d71921430a</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_LOCAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga5ff73525b7503a91cebfadabd347af50</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_GLOBAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8aec5246b3ffd6d5ed8cd33fef73932f</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_EXTERNAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga1f457747020689dd37f02977132805e4</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaabf4d21272e8abbfab5db78a1f932687</anchor>
      <arglist>(metricHandle, name, unit, type, context)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gac4808a743c67e6f1284dce290695ecff</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gae56cb2e66065f563f0b7ab030c17c538</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_DOUBLE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga31e598aa18b69054fcdfb28e0032fad0</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_CREATE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaaaf62bc0ce216cac48c788919735d9c3</anchor>
      <arglist>(userTopology, name, nDims)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_ADD_DIM</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga614e23fb934641599a9d1592b81201fa</anchor>
      <arglist>(userTopology, size, periodic, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga1301cb8d825c425c9ae16d94299a08f3</anchor>
      <arglist>(userTopology)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_SET_COORDS</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gafccee35576f4754cb05b51cfd2583c3c</anchor>
      <arglist>(userTopology, nDims,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gab5b2732699c4885ed7052b66a8c41383</anchor>
      <arglist>(userTopology)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga20640122ace776d083a163fd86fb46f9</anchor>
      <arglist>(name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_ON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga4a74d67519387ca834adbd6661afa818</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_OFF</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gafa31b2ab267a4997f7b62bcc38ed5ac9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_IS_ON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaa477c37a05e90ed79d1d7ae9c1b9a691</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>SCOREP_User_Types.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/include/scorep/</path>
    <filename>SCOREP__User__Types_8h</filename>
    <includes id="SCOREP__PublicTypes_8h" name="SCOREP_PublicTypes.h" local="no" imported="no">scorep/SCOREP_PublicTypes.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_INVALID_PARAMETER</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>a8255dceb835519d1a95b5812d99be9c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_INVALID_REGION</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>a46062b8aeffded08e6eb63d9d70d734b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_INVALID_TOPOLOGY</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>ac7174a4fca6f2574c060de4e174d91aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_COMMON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga96dcf81f3fa148d0fc2a3858a1e182d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_FUNCTION</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gae52916626f11ce0adb0b952c99f7c4b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_LOOP</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gacdf69e2b56c75e550dec7207c6aa2243</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_DYNAMIC</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga21f6417ac8c1c15291bcf0e78331c988</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_PHASE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8697e0979e050043887e238c33df83f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gacfaf06b575d4862f1b5324a075ea335b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga6eab5108fecda6f8d231158609285913</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_DOUBLE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga22239a02a57f190daf85a04fb2e790c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_CONTEXT_GLOBAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga198befe14fea1cd37c30293dfd41c0c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_CONTEXT_CALLPATH</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga0870aa787dc35f57815c33537efe02cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct SCOREP_User_Topology *</type>
      <name>SCOREP_User_CartesianTopologyHandle</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>a7532d28b6ae0a41e30ba4e453097ba23</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>SCOREP_User_MetricType</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>a256f8f899fe697e970f6b785c17c7914</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t</type>
      <name>SCOREP_User_ParameterHandle</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>aa00c20701de660fba257bdf3128b41cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct SCOREP_User_Region *</type>
      <name>SCOREP_User_RegionHandle</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>a5456c4b230a64442e9280f47e2dac962</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>SCOREP_User_RegionType</name>
      <anchorfile>SCOREP__User__Types_8h.html</anchorfile>
      <anchor>aeebec87dcfc82b990cb2164f36dd4f72</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_COMMON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga96dcf81f3fa148d0fc2a3858a1e182d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_FUNCTION</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gae52916626f11ce0adb0b952c99f7c4b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_LOOP</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gacdf69e2b56c75e550dec7207c6aa2243</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_DYNAMIC</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga21f6417ac8c1c15291bcf0e78331c988</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_PHASE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8697e0979e050043887e238c33df83f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gacfaf06b575d4862f1b5324a075ea335b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga6eab5108fecda6f8d231158609285913</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_DOUBLE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga22239a02a57f190daf85a04fb2e790c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_CONTEXT_GLOBAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga198befe14fea1cd37c30293dfd41c0c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_CONTEXT_CALLPATH</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga0870aa787dc35f57815c33537efe02cd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCOREP_Metric_Plugin_Info</name>
    <filename>structSCOREP__Metric__Plugin__Info.html</filename>
    <member kind="variable">
      <type>int32_t(*</type>
      <name>add_counter</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a772e897a7e8113b5c82792d8899f1d4c</anchor>
      <arglist>)(char *metric_name)</arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>delta_t</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a44a2ab20307bb9f44c986772df922c6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>finalize</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a47c7086fff6e72e3ca197d483aba2502</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>uint64_t(*</type>
      <name>get_all_values</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a45a52a4753ab3c601981041552fd9c5e</anchor>
      <arglist>)(int32_t id, SCOREP_MetricTimeValuePair **time_value_list)</arglist>
    </member>
    <member kind="variable">
      <type>uint64_t(*</type>
      <name>get_current_value</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>aeb1db6b96675dac81bfbb6effa81366f</anchor>
      <arglist>)(int32_t id)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_Metric_Plugin_MetricProperties *(*</type>
      <name>get_event_info</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a087f24f475a628a1ac92b35824393fe8</anchor>
      <arglist>)(char *token)</arglist>
    </member>
    <member kind="variable">
      <type>bool(*</type>
      <name>get_optional_value</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a9040874b7af59b330559472623c3a428</anchor>
      <arglist>)(int32_t id, uint64_t *value)</arglist>
    </member>
    <member kind="variable">
      <type>int32_t(*</type>
      <name>initialize</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>aeeaad74fc73eab3cba16e49c2476ee5a</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>plugin_version</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a4f17bc4134f44442e43623bc7e587266</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>reserved</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>af0cfb67a7b18826065a11700dd0d230d</anchor>
      <arglist>[92]</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricPer</type>
      <name>run_per</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>ad0f4d332ca0a1122dfa7ab3d6e1b94c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>set_clock_function</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>ac9ad0f2a8f6d1e1e987ed43d3db5f9a6</anchor>
      <arglist>)(uint64_t(*clock_time)(void))</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricSynchronicity</type>
      <name>sync</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>ae0ce349e670408edd2d6b827eb651d98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>synchronize</name>
      <anchorfile>structSCOREP__Metric__Plugin__Info.html</anchorfile>
      <anchor>a3e7baaaacd022944211dcfe716c9395a</anchor>
      <arglist>)(bool is_responsible, SCOREP_MetricSynchronizationMode sync_mode)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCOREP_Metric_Plugin_MetricProperties</name>
    <filename>structSCOREP__Metric__Plugin__MetricProperties.html</filename>
    <member kind="variable">
      <type>SCOREP_MetricBase</type>
      <name>base</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>a946859e0e1fa6bca9e42f8eee3e8022f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>description</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>a9b1e96a0ae6c5a6d45da057ce2cbde3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int64_t</type>
      <name>exponent</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>a071dd5a962fc15fc0e3fa2eb6e97bbec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricMode</type>
      <name>mode</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>a5a9e17152a991a44a3e074119bb7f07c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>name</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>ace618c2d2a50f423b963e5615ed6c502</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>unit</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>ab2f211fce95a8b3ad2fa5781cdc44458</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricValueType</type>
      <name>value_type</name>
      <anchorfile>structSCOREP__Metric__Plugin__MetricProperties.html</anchorfile>
      <anchor>a8461d69ecfd5ba60ccecd0da2921090c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCOREP_Metric_Properties</name>
    <filename>structSCOREP__Metric__Properties.html</filename>
    <member kind="variable">
      <type>SCOREP_MetricBase</type>
      <name>base</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>ad536799cc8bed9c092d6381d45c9a0dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>description</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>adf3a2f5393a286e208a400d464cbec8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int64_t</type>
      <name>exponent</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>a1f9cbbd369dc26e41146af09d7bc9238</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricMode</type>
      <name>mode</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>a84d31ac6a1ece2881b223584b8fc0b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>name</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>a2b2b1c12e1ed5db0cdd2cb39ddd5a103</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricProfilingType</type>
      <name>profiling_type</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>af4ce9e42e171a4d80802e6f03659c14b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricSourceType</type>
      <name>source_type</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>aed9d787efc1e2e2ab54c75b67bbbf966</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>unit</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>a51e41e457b2ea4746467fd6eb42c19f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricValueType</type>
      <name>value_type</name>
      <anchorfile>structSCOREP__Metric__Properties.html</anchorfile>
      <anchor>a42951d8da790a1511c3daa25c1f4c1eb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCOREP_MetricTimeValuePair</name>
    <filename>structSCOREP__MetricTimeValuePair.html</filename>
    <member kind="variable">
      <type>uint64_t</type>
      <name>timestamp</name>
      <anchorfile>structSCOREP__MetricTimeValuePair.html</anchorfile>
      <anchor>aaaf11b68a483378fe20e163f789a543a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>value</name>
      <anchorfile>structSCOREP__MetricTimeValuePair.html</anchorfile>
      <anchor>abb30a90bd4d2ed6bd6e3db924fe73ab6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCOREP_SubstratePluginCallbacks</name>
    <filename>structSCOREP__SubstratePluginCallbacks.html</filename>
    <member kind="variable">
      <type>SCOREP_CallingContextHandle(*</type>
      <name>SCOREP_CallingContextHandle_GetParent</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a1ba1b41ac1a7d18e9ddd8b36623998d9</anchor>
      <arglist>)(SCOREP_CallingContextHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_RegionHandle(*</type>
      <name>SCOREP_CallingContextHandle_GetRegion</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a4dc597d1391be6c3e28b064977134191</anchor>
      <arglist>)(SCOREP_CallingContextHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>SCOREP_ConfigManifestSectionEntry</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a1d1818372eb9611e08c965b72aa771c2</anchor>
      <arglist>)(FILE *out, const char *fileName, const char *descriptionFormatString,...)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>SCOREP_ConfigManifestSectionHeader</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a4a056bb866342732d9f5767db298b6b5</anchor>
      <arglist>)(FILE *out, const char *section)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_GetExperimentDirName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>adacc1b82149ec22dfb73086334a7b564</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Allgather</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a6f8dbb8afdb00cb9205d955e731e1d2c</anchor>
      <arglist>)(const void *sendbuf, void *recvbuf, int count, SCOREP_Ipc_Datatype datatype)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Allreduce</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a7d529becf6ecf66aaaa68691e8e9935b</anchor>
      <arglist>)(const void *sendbuf, void *recvbuf, int count, SCOREP_Ipc_Datatype datatype, SCOREP_Ipc_Operation operation)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Barrier</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a63b5f163f97696abe1ea4b1319a6a940</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Bcast</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>abc7ee664b450ef5502ad5516fc9b60ec</anchor>
      <arglist>)(void *buf, int count, SCOREP_Ipc_Datatype datatype, int root)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Gather</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a0222048a192b0cb20977e1962a51d999</anchor>
      <arglist>)(const void *sendbuf, void *recvbuf, int count, SCOREP_Ipc_Datatype datatype, int root)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Gatherv</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a1b5a41bcb6fa4b7ead5a659b11b322b3</anchor>
      <arglist>)(const void *sendbuf, int sendcount, void *recvbuf, const int *recvcnts, SCOREP_Ipc_Datatype datatype, int root)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_GetRank</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a81c1563f0c9a8c5d05086bfd05697e0f</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_GetSize</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a2e81a78f910f799b54f07e6100690b23</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Recv</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a98fb87d1e1805ae6832d57288f290a9f</anchor>
      <arglist>)(void *buf, int count, SCOREP_Ipc_Datatype datatype, int source)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Reduce</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>adb215139591730297b7f4f6a13d5a6ee</anchor>
      <arglist>)(const void *sendbuf, void *recvbuf, int count, SCOREP_Ipc_Datatype datatype, SCOREP_Ipc_Operation operation, int root)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Scatter</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a82109526db34e19ead1c85466e8ec14a</anchor>
      <arglist>)(const void *sendbuf, void *recvbuf, int count, SCOREP_Ipc_Datatype datatype, int root)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Scatterv</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ac3c258020ebc1dd415f5857e4712f05b</anchor>
      <arglist>)(const void *sendbuf, const int *sendcounts, void *recvbuf, int recvcount, SCOREP_Ipc_Datatype datatype, int root)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>SCOREP_Ipc_Send</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ac7d5f44a7e8c36268b23b5dd198e0134</anchor>
      <arglist>)(const void *buf, int count, SCOREP_Ipc_Datatype datatype, int dest)</arglist>
    </member>
    <member kind="variable">
      <type>void *(*</type>
      <name>SCOREP_Location_GetData</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ac73a3d496031c2cc7725159a8cc2a507</anchor>
      <arglist>)(const struct SCOREP_Location *locationData, size_t plugin_id)</arglist>
    </member>
    <member kind="variable">
      <type>uint64_t(*</type>
      <name>SCOREP_Location_GetGlobalId</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a25e472e930f991b50bfe14b6080b0f24</anchor>
      <arglist>)(const struct SCOREP_Location *locationData)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t(*</type>
      <name>SCOREP_Location_GetId</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a12cf3c888dc7588261336d8957a1d44d</anchor>
      <arglist>)(const struct SCOREP_Location *locationData)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_Location_GetName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a311e1862c9a5f3e41fcdb0564de5a630</anchor>
      <arglist>)(const struct SCOREP_Location *locationData)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_LocationType(*</type>
      <name>SCOREP_Location_GetType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a31b089d5cc186b7a918656eaf26ecb0f</anchor>
      <arglist>)(const struct SCOREP_Location *locationData)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>SCOREP_Location_SetData</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a533402c64329549d6964e5988d976d74</anchor>
      <arglist>)(const struct SCOREP_Location *locationData, size_t plugin_id, void *data)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>SCOREP_Metric_WriteAsynchronousMetrics</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a69c242016ec3d426b23902785c482cfa</anchor>
      <arglist>)(struct SCOREP_Location *location, SCOREP_Substrates_WriteMetricsCb cb)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>SCOREP_Metric_WriteStrictlySynchronousMetrics</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>abcfe2e4d9e3785041296c38f30f6d782</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_Substrates_WriteMetricsCb cb)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>SCOREP_Metric_WriteSynchronousMetrics</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a408c722e7b91502621a0055f0e69693f</anchor>
      <arglist>)(struct SCOREP_Location *location, uint64_t timestamp, SCOREP_Substrates_WriteMetricsCb cb)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricMode(*</type>
      <name>SCOREP_MetricHandle_GetMode</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ae8fe046a767c5376adf96045632d6697</anchor>
      <arglist>)(SCOREP_MetricHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_MetricHandle_GetName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ab6e0c953b5d0344525ea369bb471a1d0</anchor>
      <arglist>)(SCOREP_MetricHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricProfilingType(*</type>
      <name>SCOREP_MetricHandle_GetProfilingType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a55dc32632d4ce5f0d81c0dc89e323b46</anchor>
      <arglist>)(SCOREP_MetricHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricSourceType(*</type>
      <name>SCOREP_MetricHandle_GetSourceType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a1602e1a753544e7e8965e68afb68eada</anchor>
      <arglist>)(SCOREP_MetricHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricValueType(*</type>
      <name>SCOREP_MetricHandle_GetValueType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a865e1d3935c5f99361a1363494d31eca</anchor>
      <arglist>)(SCOREP_MetricHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_ParadigmClass(*</type>
      <name>SCOREP_ParadigmHandle_GetClass</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a21f2596f51f04807e281608a3a7a9264</anchor>
      <arglist>)(SCOREP_ParadigmHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_ParadigmHandle_GetName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a13469ddc05386c0c07b608c42432edca</anchor>
      <arglist>)(SCOREP_ParadigmHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_ParadigmType(*</type>
      <name>SCOREP_ParadigmHandle_GetType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>aefc0055c14d8cf07af3245403d3bd3cf</anchor>
      <arglist>)(SCOREP_ParadigmHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_ParameterHandle_GetName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a46b8e287db736c858944a9c9348d845c</anchor>
      <arglist>)(SCOREP_ParameterHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_ParameterType(*</type>
      <name>SCOREP_ParameterHandle_GetType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a58a00bde72ddd13b481a1932fcd7e549</anchor>
      <arglist>)(SCOREP_ParameterHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_LineNo(*</type>
      <name>SCOREP_RegionHandle_GetBeginLine</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a49bac2887a25987b0472c861b05b886b</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_RegionHandle_GetCanonicalName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a507864515d84f59557dc151ac45b0b37</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_LineNo(*</type>
      <name>SCOREP_RegionHandle_GetEndLine</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ac7e7a3acf5ca571a861094be86387c93</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_RegionHandle_GetFileName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>af860dbbad56223b7d8956680dd1201e2</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t(*</type>
      <name>SCOREP_RegionHandle_GetId</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a967b935629e7197083af9911b6a98294</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_RegionHandle_GetName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a654072e24258ca508ec979cb5ddb46ad</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_ParadigmType(*</type>
      <name>SCOREP_RegionHandle_GetParadigmType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>aeec6665577f4d2611c847b26cfe8d729</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_RegionType(*</type>
      <name>SCOREP_RegionHandle_GetType</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>aac320c54cc71c2aea50230dd94fb8082</anchor>
      <arglist>)(SCOREP_RegionHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const SCOREP_MetricHandle *(*</type>
      <name>SCOREP_SamplingSetHandle_GetMetricHandles</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ad1b849615302b250d5e2e49c48a22e7c</anchor>
      <arglist>)(SCOREP_SamplingSetHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricOccurrence(*</type>
      <name>SCOREP_SamplingSetHandle_GetMetricOccurrence</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a744d261e4841b381fdb889eba425c994</anchor>
      <arglist>)(SCOREP_SamplingSetHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>uint8_t(*</type>
      <name>SCOREP_SamplingSetHandle_GetNumberOfMetrics</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>ae4896113f6b2faecbb8561c7f2f68208</anchor>
      <arglist>)(SCOREP_SamplingSetHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_SamplingSetClass(*</type>
      <name>SCOREP_SamplingSetHandle_GetSamplingSetClass</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>aad3d382fbbfbd38d5765966599cc6e6a</anchor>
      <arglist>)(SCOREP_SamplingSetHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>SCOREP_MetricScope(*</type>
      <name>SCOREP_SamplingSetHandle_GetScope</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a4955add63025c2b9ff2a64ab7558aa7d</anchor>
      <arglist>)(SCOREP_SamplingSetHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>bool(*</type>
      <name>SCOREP_SamplingSetHandle_IsScoped</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a9cfc9ee6d073af990ce296ffc5653aff</anchor>
      <arglist>)(SCOREP_SamplingSetHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_SourceFileHandle_GetName</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>a11a2176392ca24a5771bdfda1ca0c2a1</anchor>
      <arglist>)(SCOREP_SourceFileHandle handle)</arglist>
    </member>
    <member kind="variable">
      <type>const char *(*</type>
      <name>SCOREP_StringHandle_Get</name>
      <anchorfile>structSCOREP__SubstratePluginCallbacks.html</anchorfile>
      <anchor>abba11ce6042518018f49ed4c95e59858</anchor>
      <arglist>)(SCOREP_StringHandle handle)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SCOREP_SubstratePluginInfo</name>
    <filename>structSCOREP__SubstratePluginInfo.html</filename>
    <member kind="variable">
      <type>void(*</type>
      <name>activate_cpu_location</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>ab0dfb2a5e35c4dfb131b28c5e412d531</anchor>
      <arglist>)(const struct SCOREP_Location *location, const struct SCOREP_Location *parentLocation, uint32_t forkSequenceCount)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>assign_id</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>afafe19469d8bd367ecbd90abe6dc9394</anchor>
      <arglist>)(size_t pluginId)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>core_task_complete</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a7d100aecc610c9787a3c58c34dc974d3</anchor>
      <arglist>)(const struct SCOREP_Location *location, SCOREP_TaskHandle taskHandle)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>core_task_create</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a45ffc744fcc26bbddf9f71c8032f075e</anchor>
      <arglist>)(const struct SCOREP_Location *location, SCOREP_TaskHandle taskHandle)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>create_location</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a39d6534096a6ca9d9a0b846be6f9eca4</anchor>
      <arglist>)(const struct SCOREP_Location *location, const struct SCOREP_Location *parentLocation)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>deactivate_cpu_location</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a89a3278e263570318571f437ed91c838</anchor>
      <arglist>)(const struct SCOREP_Location *location, const struct SCOREP_Location *parentLocation)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>delete_location</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a41b86a5e0bc5daa7c76f274edd42afb6</anchor>
      <arglist>)(const struct SCOREP_Location *location)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>dump_manifest</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>ad7e6df8d9a6ff0bc42aa10945d5d6ad2</anchor>
      <arglist>)(FILE *manifestFile, const char *relativeSourceDir, const char *targetDir)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>finalize</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>adbadbf92e832b5e59808fea790632382</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t(*</type>
      <name>get_event_functions</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>aca1e33bb5df50b3b9fc60994452ea09e</anchor>
      <arglist>)(SCOREP_Substrates_Mode mode, SCOREP_Substrates_Callback **functions)</arglist>
    </member>
    <member kind="variable">
      <type>bool(*</type>
      <name>get_requirement</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a01c64f9532e723084907f527f6e89586</anchor>
      <arglist>)(SCOREP_Substrates_RequirementFlag flag)</arglist>
    </member>
    <member kind="variable">
      <type>int(*</type>
      <name>init</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>ab3b377e52787222cf05fc6e99353e0f6</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>init_mpp</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a25f18d03f528f84731a403cdc3801a42</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>new_definition_handle</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a0332f4c06383af4d1c34d4ee9b44f3ac</anchor>
      <arglist>)(SCOREP_AnyHandle handle, SCOREP_HandleType type)</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>plugin_version</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a020b5e6467699babc5131a02b0a00333</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>pre_unify</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>aa0a880d38e4411b67c5ce15dd4cabc22</anchor>
      <arglist>)(void)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>set_callbacks</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a6cd4bf104da3a44edbddd5f740a72de5</anchor>
      <arglist>)(const SCOREP_SubstratePluginCallbacks *callbacks, size_t size)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>undeclared</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a89b4b4d5d9800a4ccb49167833626829</anchor>
      <arglist>[SCOREP_SUBSTRATE_PLUGIN_UNDEFINED_MANAGEMENT_FUNCTIONS])(void)</arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>write_data</name>
      <anchorfile>structSCOREP__SubstratePluginInfo.html</anchorfile>
      <anchor>a57f5e2bafd3c28149670d5801054bc66</anchor>
      <arglist>)(void)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>SCOREP_User</name>
    <title>Score-P User Adapter</title>
    <filename>group__SCOREP__User.html</filename>
    <file>SCOREP_User.h</file>
    <file>SCOREP_User_Types.h</file>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_OA_PHASE_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga40f15c9d9ab7069a6b2e86ab016f6c8b</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_OA_PHASE_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gadc3d51e99a65b4094ce8d14be406c713</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaab4b3ccc2b169320c1d3bf7fe19165f9</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gad481ce21b169390edb4cf6d206359672</anchor>
      <arglist>(handle, name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga36bc4808f2cbdfd75f9a05d2124698d1</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_ENTER</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8c8f772145f95dce57dcf86b6998365c</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8fff2e6053e2a36a4c3421e8114a912e</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga23e865fc48814d8f1a73f2138a69c749</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_BEGIN</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga6cd32d0be80a23887723f728a6a9d0eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_FUNC_END</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaf86321e31c824a10c9907e9961052f88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_GLOBAL_REGION_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga7019f070cfc0ff854e701a9aeb9e8988</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_GLOBAL_REGION_EXTERNAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaf0c9dfaad79f9844fe0cb2464763bb65</anchor>
      <arglist>(handle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gad4d135ed8a7f81100125658cd402d78e</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga08175aaf74cc890748fdd8d858e7f993</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_PARAMETER_STRING</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga4cf20238efa2cfa9098c52d71921430a</anchor>
      <arglist>(name, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_LOCAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga5ff73525b7503a91cebfadabd347af50</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_GLOBAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8aec5246b3ffd6d5ed8cd33fef73932f</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_EXTERNAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga1f457747020689dd37f02977132805e4</anchor>
      <arglist>(metricHandle)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaabf4d21272e8abbfab5db78a1f932687</anchor>
      <arglist>(metricHandle, name, unit, type, context)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gac4808a743c67e6f1284dce290695ecff</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gae56cb2e66065f563f0b7ab030c17c538</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_DOUBLE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga31e598aa18b69054fcdfb28e0032fad0</anchor>
      <arglist>(metricHandle, value)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_CREATE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaaaf62bc0ce216cac48c788919735d9c3</anchor>
      <arglist>(userTopology, name, nDims)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_ADD_DIM</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga614e23fb934641599a9d1592b81201fa</anchor>
      <arglist>(userTopology, size, periodic, name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_INIT</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga1301cb8d825c425c9ae16d94299a08f3</anchor>
      <arglist>(userTopology)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_SET_COORDS</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gafccee35576f4754cb05b51cfd2583c3c</anchor>
      <arglist>(userTopology, nDims,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_CARTESIAN_TOPOLOGY_DEFINE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gab5b2732699c4885ed7052b66a8c41383</anchor>
      <arglist>(userTopology)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga20640122ace776d083a163fd86fb46f9</anchor>
      <arglist>(name, type)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_ON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga4a74d67519387ca834adbd6661afa818</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_OFF</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gafa31b2ab267a4997f7b62bcc38ed5ac9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_RECORDING_IS_ON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gaa477c37a05e90ed79d1d7ae9c1b9a691</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_COMMON</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga96dcf81f3fa148d0fc2a3858a1e182d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_FUNCTION</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gae52916626f11ce0adb0b952c99f7c4b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_LOOP</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gacdf69e2b56c75e550dec7207c6aa2243</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_DYNAMIC</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga21f6417ac8c1c15291bcf0e78331c988</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_REGION_TYPE_PHASE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga8697e0979e050043887e238c33df83f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_INT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>gacfaf06b575d4862f1b5324a075ea335b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_UINT64</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga6eab5108fecda6f8d231158609285913</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_TYPE_DOUBLE</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga22239a02a57f190daf85a04fb2e790c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_CONTEXT_GLOBAL</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga198befe14fea1cd37c30293dfd41c0c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_USER_METRIC_CONTEXT_CALLPATH</name>
      <anchorfile>group__SCOREP__User.html</anchorfile>
      <anchor>ga0870aa787dc35f57815c33537efe02cd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>Public</name>
    <title>type definitions and enums used in Score-P</title>
    <filename>group__Public.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_ALL_TARGET_RANKS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gadcedcc15f54c90fed84776b728c7427e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_EXIT_STATUS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gab3efa3ee03b9ea19f50cedb20f505c46</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_LINE_NO</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa902c1f27bc699a3177efbe6cecc7264</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_METRIC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga7f927936deaeb989b4ea038a1ef9745d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_PARADIGM</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga4aa85f3b492f91edf67ef0b0aeb3870e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_REGION</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gabfb6015f4987baa2f1d3b4965fbb1027</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_ROOT_RANK</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga43f526b8899d65da08ca24e556f12080</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_SAMPLING_SET</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga00bb9822a4acd564158c741ff9f67b78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_INVALID_SOURCE_FILE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gab7bfb29a1590fa3d0ee63ad002eb5b23</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_LOCATION_TYPES</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaac8240c4c70b7b8aee9d63d0a138c75c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOREP_MOVABLE_NULL</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga416820d06bb171c07dbb66010862ffc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>SCOREP_Allocator_MovableMemory</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga073a5d370b1bcdf739df1e75380a03b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_Allocator_MovableMemory</type>
      <name>SCOREP_AnyHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa674d5e3722f8c9b7c1d23a475603365</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int64_t</type>
      <name>SCOREP_ExitStatus</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gad8d146ff25ac3d3e8baa8f9103db2ca9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint32_t</type>
      <name>SCOREP_LineNo</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga1dcf04ed0004756cabd415fba210750a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_MetricHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga4faa73ab360d2a1c5bc278ed49669e64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>SCOREP_MpiRank</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga3c9d908fb280602e92791134cfb57e01</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>uint64_t</type>
      <name>SCOREP_MpiRequestId</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga5f47cddd80bc28f7c01c2192334c4d96</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_ParadigmHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gab5dfdc503fa5ae4cd5c1545d2e9f8855</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_RegionHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga35c3f5ba0398e83f528b4241c8002c06</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_SamplingSetHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga244d2bfaa62f4d1fd13fa7ab5d16218a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SCOREP_AnyHandle</type>
      <name>SCOREP_SourceFileHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga9c28c3cffcfd47763efd1607dd63f767</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct SCOREP_Task *</type>
      <name>SCOREP_TaskHandle</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gad6073c055f49446ef7e60e7ee95a91a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_CollectiveType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga31673b3012520b84dfc10cf9d2e50032</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_BARRIER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aa26c04527ba802ed1e683ae26b94d13f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_BROADCAST</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a6c81cef42738c5fe52a40a697e2f2ec0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_GATHER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a3ca2c5ed3773a8b5330fca73b3a0517a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_GATHERV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a36d8b3c66563d98bb65986eb6dd481a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_SCATTER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a602dfd1852c7a8550be71a364cf72796</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_SCATTERV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a5fe5314366351990bed93a8f03f340ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLGATHER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032ad183ed1e931a746fadccf6bcbe95cbea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLGATHERV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aed0135d39789398c88c323a995703328</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLTOALL</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a8562667889a5a8dd1b1bdbbd437aec79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLTOALLV</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aa2092bb78bd8676afdbaa01ef6bea213</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLTOALLW</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032abe6565488decc2cdd9b0ef68c6c9f455</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLREDUCE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032afcfd8c6abb8206f1cb7ff41322c705b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_REDUCE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aa7591423702cab3c95246dad2711c542</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_REDUCE_SCATTER</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032afe4d3f5084a8eb696700f4723851f775</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_REDUCE_SCATTER_BLOCK</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a0a3da23b2e9716470a28a504dffbc41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_SCAN</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a2d11789b83703e2b49dc1b786fa00006</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_EXSCAN</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a6e9507c9ef3f90d11cd638d650b475e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_CREATE_HANDLE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a74e51c164e843d05299b56b4fcc734a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_DESTROY_HANDLE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032aca01f3589fe5f36bd5dc374195a9fec6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_ALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032addd31856975f3d2a9ab9f583aa567303</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_DEALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a29e3488193957364351940cd63091fba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_CREATE_HANDLE_AND_ALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a59cf430980bcd543835508a09342322e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_COLLECTIVE_DESTROY_HANDLE_AND_DEALLOCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga31673b3012520b84dfc10cf9d2e50032a0e0602af785147df980f7f5e69e104d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoAccessMode</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga3aea792cd0d6e5a675ba9819fa71282a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aad84b6b2de05da72ec3be0d920c9c4d89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_READ_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aa801952fc2320b38adf386c46ccea1805</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_WRITE_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aafb29c9c6505ff890bc32405fd04af53c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_READ_WRITE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aa077a947e8f08f2624f4bd21209c2613f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_EXECUTE_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aaf2e9988b6f16bae045bd56460be910fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_ACCESS_MODE_SEARCH_ONLY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3aea792cd0d6e5a675ba9819fa71282aadf10faee7fa11a3cf2a8eb98a910ec4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoCreationFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga2b0045dcee30b266b986c6dad60ce94d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dad0b101a848e6aa802732371126784ea9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_CREATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dada19c77b3726769e981c14ce73b42073</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_TRUNCATE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da7d9be856ea196c350943eeda3dd90235</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_DIRECTORY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da389eb43db1302bfc9e3f3954e71ba09a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_EXCLUSIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da8a59f6f509bb17743586727860a11ece</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NO_CONTROLLING_TERMINAL</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dac403f7fb601cff2bb547d273c5656f48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NO_FOLLOW</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da9fd3144d339a47dce06f8ed10c362067</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_PATH</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da44f5040ed948f419535ad63666bc2043</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_TEMPORARY_FILE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dafd76b21e02eda8cc023e66bdd45e6fd4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_LARGEFILE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da2b17a70d56ead493b62cc3d99313d403</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_NO_SEEK</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94da403da02c9259e5c88f5a5feb18a3b89a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_CREATION_FLAG_UNIQUE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga2b0045dcee30b266b986c6dad60ce94dab5ee7b6d5ae02998f1dab2067d9539cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoOperationFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga83f3e78d8bd291fb70de8d849d4bd2f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9aa2d790e5c24464ad10b9655641a133a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_BLOCKING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9a8d1dd38f75dfddbbe3a27ba447543089</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_NON_BLOCKING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9a095fd84ee82d81df647c7a2616df108d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_COLLECTIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9aac53afded8a6cdcf3d022c4604153724</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_FLAG_NON_COLLECTIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga83f3e78d8bd291fb70de8d849d4bd2f9aa55839e696b8e426c1cb445974965c95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoOperationMode</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga3981a3958c6fe3ccab5acafbf7ad29ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_MODE_READ</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3981a3958c6fe3ccab5acafbf7ad29baa91656cd813fc67ee198288a3c3735cbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_MODE_WRITE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3981a3958c6fe3ccab5acafbf7ad29baafbd448d4186af6dadf8658834f5e7efe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_OPERATION_MODE_FLUSH</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga3981a3958c6fe3ccab5acafbf7ad29baa14354fd9fc6cfd6bf27900529652ae49</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoParadigmType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga8a40e0b4ac99eb2434183edb26a6807d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoSeekOption</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga8815c891a0fc20fca86f5c4a674b8c59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_FROM_START</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59ac37ebe46277c781aa5aa167b4dfde708</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_FROM_CURRENT</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59adaee654423132182f27e6e419add25a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_FROM_END</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59aeaeb74103c7f015f1b56b2fe3a9b6dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_DATA</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59af7a5a09492ce37f475901d0553537968</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_HOLE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59a09785f685343a03054812a8ace7bce89</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_SEEK_INVALID</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga8815c891a0fc20fca86f5c4a674b8c59aff649939b6f3259e8d2bbc2ec48ecbe0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_IoStatusFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga4d9ed0834a9c13b22aa737288cd8b184</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_NONE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a24058cd8e998ea9329603584dea0f45e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_CLOSE_ON_EXEC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184ac6b2c84635cc1fbf69bd3e65020ed69f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_APPEND</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a58e92afe762426714c8d05271faac3a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_NON_BLOCKING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a64de3b345d7f0dd4fae25e9de32f3ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_ASYNC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a4ad14d9f9ca305196914ceb458715fdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_SYNC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a68c7e9ba02d1823efa9e0081e2d03b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_DATA_SYNC</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a0e54a49c0256df0930a8d1c69614c4a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_AVOID_CACHING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a611cc98ffdae579551919ae49aa06fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_NO_ACCESS_TIME</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184ac7f64e103488476b07e18c5336399090</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_IO_STATUS_FLAG_DELETE_ON_CLOSE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga4d9ed0834a9c13b22aa737288cd8b184a74764896a436bd5feed5deb293d42cf6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Ipc_Datatype</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga6eec6de9cc89e48af2be1035b0155899</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Ipc_Operation</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa61cd8bcd44b6cc89cc33ae16c8da992</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_LocationType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaa9e2e42350b85c45c06a32ccf8cdf5d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_LOCATION_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggaa9e2e42350b85c45c06a32ccf8cdf5d4a00c13fa42490847d45ac4a91140a895c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_LockType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga13e99a7883e8e4d3468320f3fae14887</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_LOCK_EXCLUSIVE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga13e99a7883e8e4d3468320f3fae14887a37a94628310f7f083dee77a253a4f1a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_LOCK_SHARED</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga13e99a7883e8e4d3468320f3fae14887a6e12d4fea638280cb3b7d0a1de7d21e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_LOCK_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga13e99a7883e8e4d3468320f3fae14887a82790f80b798a36195230de5bd0b8728</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricOccurrence</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga6e2f8848981c6264b999fe925488a516</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_OCCURRENCE_SYNCHRONOUS_STRICT</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a660126448f2b715915a832b1cc87fdaa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_OCCURRENCE_SYNCHRONOUS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a767362f2cfb151b03f24db2e86c5d783</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_OCCURRENCE_ASYNCHRONOUS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a333e3e8749f4f63359fa1467ed3346fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_METRIC_OCCURRENCE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga6e2f8848981c6264b999fe925488a516a45cdc4cb56534925c0fef4cc5ffc82e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_MetricScope</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gabc0b01d887d84683fca8bd5aface6ae4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_LOCATION</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a12c4fa145873068939247b08c260c23e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_LOCATION_GROUP</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a060e44dad9b1d52ec44a04306e8e1028</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_SYSTEM_TREE_NODE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a114a3d49db709d47368ed7ee0c1871dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_METRIC_SCOPE_GROUP</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a94d0841c12dc62bb71eb2111f0eeecda</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_METRIC_SCOPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabc0b01d887d84683fca8bd5aface6ae4a9dad2506696b26ae8ce99e70e94efa25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_ParadigmClass</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga215b57f4b6077f5b49cf4d07789426fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_PARADIGM_CLASS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga215b57f4b6077f5b49cf4d07789426faac74f1dedc00de6a3b3033fe717c4141d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_ParadigmType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ga54ea902852bed473f674ed1f9cc8e523</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_PARADIGM_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gga54ea902852bed473f674ed1f9cc8e523a3b1802b3adbb923310cb178edb467ebe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_ParameterType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gad5610b49b0b12b5d3f6c0c4a09924afd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_PARAMETER_INT64</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afda4ed26dbfa2eef7a8502448210f3756da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_PARAMETER_UINT64</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afda437b58e6aece0c9e5209b35ab0068f65</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_PARAMETER_STRING</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afdaf77db7854e898dce09f54d24c733bc26</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_PARAMETER_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggad5610b49b0b12b5d3f6c0c4a09924afda2a1034f6b346c65658a69e725051319e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RegionType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gaeb4e4c2fbdfe182a263c8d9d41aa0ffb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_REGION_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggaeb4e4c2fbdfe182a263c8d9d41aa0ffbae8e6e39a524dd4df1138ca3c9586cccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RmaAtomicType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gada9d37396e7a2b09f87f148f08eb620c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RmaSyncLevel</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gadf190946dbad8ff7875f457f808bc90b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_RmaSyncType</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gabe2ec192d5ad0f1971942ba25600e69f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_INVALID_RMA_SYNC_TYPE</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggabe2ec192d5ad0f1971942ba25600e69fa22a6a1719aeb48521652df5088ca0e7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_SamplingSetClass</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gacae06b5b045fb7175c1f3ac5913893ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SAMPLING_SET_ABSTRACT</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggacae06b5b045fb7175c1f3ac5913893acae4f602754ddbfedb1e9c93260d242ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SAMPLING_SET_CPU</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggacae06b5b045fb7175c1f3ac5913893aca083dcef173720235a73a5fac13bf3c63</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SAMPLING_SET_GPU</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggacae06b5b045fb7175c1f3ac5913893aca7c722818bfb090c58837db11e4172ec1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SCOREP_Substrates_RequirementFlag</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>gac35cca5dd67124a45c915f041a48d3b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_REQUIREMENT_CREATE_EXPERIMENT_DIRECTORY</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0a03f8f9a89733007a2a2a261f26d445de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_REQUIREMENT_PREVENT_ASYNC_METRICS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0a30a12a82fc69fa9f9f5de52a2a5a19e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_REQUIREMENT_PREVENT_PER_HOST_AND_ONCE_METRICS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0ab5962b10ff54123ab15e74aa39e9b9fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>SCOREP_SUBSTRATES_NUM_REQUIREMENTS</name>
      <anchorfile>group__Public.html</anchorfile>
      <anchor>ggac35cca5dd67124a45c915f041a48d3b0a2338406af0ddac42535a3f141edf16cb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>quickstart</name>
    <title>Getting Started</title>
    <filename>quickstart</filename>
    <docanchor file="quickstart" title="Score-P Quick Installation">quickinstallation</docanchor>
    <docanchor file="quickstart" title="Prerequisites">prerequisites</docanchor>
    <docanchor file="quickstart" title="General Autotools Build Options">general_autotools</docanchor>
    <docanchor file="quickstart" title="Score-P Specific Build Options">scorep_specific</docanchor>
    <docanchor file="quickstart" title="Instrumentation">quick_instrumentation</docanchor>
    <docanchor file="quickstart" title="Measurement and Analysis">quick_measurement</docanchor>
    <docanchor file="quickstart" title="Report Examination">quick_examination</docanchor>
    <docanchor file="quickstart" title="Simple Example">quick_example</docanchor>
  </compound>
  <compound kind="page">
    <name>instrumentation</name>
    <title>Application Instrumentation</title>
    <filename>instrumentation</filename>
    <docanchor file="instrumentation" title="Automatic Compiler Instrumentation">compiler_instrumentation</docanchor>
    <docanchor file="instrumentation" title="Manual Region Instrumentation">manual_instrumentation</docanchor>
    <docanchor file="instrumentation" title="Instrumentation for Parameter-Based Profiling">parameter_instrumentation</docanchor>
    <docanchor file="instrumentation" title="Measurement Control Instrumentation">control_instrumentation</docanchor>
    <docanchor file="instrumentation" title="Source-Code Instrumentation Enabling Online Access">online_access</docanchor>
    <docanchor file="instrumentation" title="Semi-Automatic Instrumentation of POMP2 User Regions">pomp_instrumentation</docanchor>
    <docanchor file="instrumentation" title="Preprocessing before POMP2 and OpenMP instrumentation">opari2_preprocessing</docanchor>
    <docanchor file="instrumentation" title="Source-Code Instrumentation Using PDT">tau_instrumentation</docanchor>
    <docanchor file="instrumentation" title="Limitations">tau_inst_limitations</docanchor>
    <docanchor file="instrumentation" title="User Library Wrapping">user_library_wrapping</docanchor>
    <docanchor file="instrumentation" title="Runtime vs Linktime Wrapping">user_library_wrapping_modes</docanchor>
    <docanchor file="instrumentation" title="Recording of I/O activities">scorep_io_recording</docanchor>
    <docanchor file="instrumentation" title="Enforce Linking of Static/Shared Score-P Libraries">scorep_link_mode</docanchor>
  </compound>
  <compound kind="page">
    <name>sampling</name>
    <title>Application Sampling</title>
    <filename>sampling</filename>
    <docanchor file="sampling" title="Introduction">sampling_introduction</docanchor>
    <docanchor file="sampling" title="Prerequisites">sampling_prerequisites</docanchor>
    <docanchor file="sampling" title="Configure Options">sampling_configure_options</docanchor>
    <docanchor file="sampling" title="libunwind">sampling_configure_options_libunwind</docanchor>
    <docanchor file="sampling" title="Sampling Related Score-P Measurement Configuration Variables">sampling_confvars</docanchor>
    <docanchor file="sampling" title="Use Cases">sampling_use_cases</docanchor>
    <docanchor file="sampling" title="Enable unwinding in instrumented programs">sampling_use_cases_unwind_instrumented_app</docanchor>
    <docanchor file="sampling" title="Instrument a hybrid parallel program and enable sampling">sampling_use_cases_instrumented_hybrid_app</docanchor>
    <docanchor file="sampling" title="Test Environment">sampling_test_environment</docanchor>
    <docanchor file="sampling" title="Instrument NAS BT-MZ code">sampling_test_environment__instrument</docanchor>
    <docanchor file="sampling" title="Run instrumented binary">sampling_test_environment_run_instrumented</docanchor>
  </compound>
  <compound kind="page">
    <name>measurement</name>
    <title>Application Measurement</title>
    <filename>measurement</filename>
    <docanchor file="measurement" title="Profiling">profiling</docanchor>
    <docanchor file="measurement" title="Parameter-Based Profiling">parameter_profiling</docanchor>
    <docanchor file="measurement" title="Phase Profiling">phase_profiling</docanchor>
    <docanchor file="measurement" title="Dynamic Region Profiling">dynamic_profiling</docanchor>
    <docanchor file="measurement" title="Clustering">clustering</docanchor>
    <docanchor file="measurement" title="Enabling additional debug output on inconsistent profiles">profile_debug_output</docanchor>
    <docanchor file="measurement" title="Tracing">tracing</docanchor>
    <docanchor file="measurement" title="Filtering">filtering</docanchor>
    <docanchor file="measurement" title="Source File Name Filter Block">source_filtering</docanchor>
    <docanchor file="measurement" title="Region Name Filter Block">region_filtering</docanchor>
    <docanchor file="measurement" title="Selective Recording">selective_recording</docanchor>
    <docanchor file="measurement" title="Trace Buffer Rewind">rewind</docanchor>
    <docanchor file="measurement" title="Recording Performance Metrics">perf_counters</docanchor>
    <docanchor file="measurement" title="PAPI Hardware Performance Counters">papi_counters</docanchor>
    <docanchor file="measurement" title="Resource Usage Counters">rusage_counters</docanchor>
    <docanchor file="measurement" title="Recording Linux Perf Metrics">metric_perf</docanchor>
    <docanchor file="measurement" title="Metric Plugins">metric_plugins</docanchor>
    <docanchor file="measurement" title="MPI Performance Measurement">mpi_adapter</docanchor>
    <docanchor file="measurement" title="Selection of MPI Groups">mpi_groups</docanchor>
    <docanchor file="measurement" title="Recording MPI Communicator Names">mpi_comm_name</docanchor>
    <docanchor file="measurement" title="CUDA Performance Measurement">cuda_adapter</docanchor>
    <docanchor file="measurement" title="OpenCL Performance Measurement">opencl_adapter</docanchor>
    <docanchor file="measurement" title="OpenACC Performance Measurement">openacc_adapter</docanchor>
    <docanchor file="measurement" title="Online Access Interface">online_access_measurement</docanchor>
    <docanchor file="measurement" title="Substrate Plugins">substrate_plugins</docanchor>
  </compound>
  <compound kind="page">
    <name>score</name>
    <title>Scoring a Profile Measurement</title>
    <filename>score</filename>
    <docanchor file="score" title="Basic usage">score_basic_usage</docanchor>
    <docanchor file="score" title="Additional per-region information">score_region_output</docanchor>
    <docanchor file="score" title="Defining and testing a filter">scorep_filter</docanchor>
    <docanchor file="score" title="Calculating the effects of recording hardware counters">score_metrics</docanchor>
  </compound>
  <compound kind="page">
    <name>workflow</name>
    <title>Performance Analysis Workflow Using Score-P</title>
    <filename>workflow</filename>
    <docanchor file="workflow" title="Program Instrumentation">program_instrumentation</docanchor>
    <docanchor file="workflow" title="Summary Measurement Collection">summary_measurement</docanchor>
    <docanchor file="workflow" title="Summary report examination">summary_examination</docanchor>
    <docanchor file="workflow" title="Summary experiment scoring">summary_scoring</docanchor>
    <docanchor file="workflow" title="Advanced summary measurement collection">advanced_summary_collection</docanchor>
    <docanchor file="workflow" title="Advanced summary report examination">advanced_summary_examination</docanchor>
    <docanchor file="workflow" title="Event trace collection and examination">trace_collection_exploration</docanchor>
  </compound>
  <compound kind="page">
    <name>installationfile</name>
    <title>Score-P INSTALL</title>
    <filename>installationfile</filename>
  </compound>
  <compound kind="page">
    <name>wrapperannex</name>
    <title>MPI wrapper affiliation</title>
    <filename>wrapperannex</filename>
    <docanchor file="wrapperannex" title="Function to group">f2g</docanchor>
    <docanchor file="wrapperannex" title="Group to function">g2f</docanchor>
  </compound>
  <compound kind="page">
    <name>metricpluginexample</name>
    <title>Score-P Metric Plugin Example</title>
    <filename>metricpluginexample</filename>
  </compound>
  <compound kind="page">
    <name>archiveannex</name>
    <title>Experiment Directory Contents</title>
    <filename>archiveannex</filename>
  </compound>
  <compound kind="page">
    <name>substratepluginexample</name>
    <title>Score-P Substrate Plugin Example</title>
    <filename>substratepluginexample</filename>
  </compound>
  <compound kind="page">
    <name>scoreptools</name>
    <title>Score-P Tools</title>
    <filename>scoreptools</filename>
    <docanchor file="scoreptools" title="scorep">scorep-main</docanchor>
    <docanchor file="scoreptools" title="scorep-config">scorep-config</docanchor>
    <docanchor file="scoreptools" title="scorep-info">scorep-info</docanchor>
    <docanchor file="scoreptools" title="scorep-score">scorep-score-tool</docanchor>
    <docanchor file="scoreptools" title="scorep-backend-info">scorep-backend-info</docanchor>
  </compound>
  <compound kind="page">
    <name>scorepmeasurementconfig</name>
    <title>Score-P Measurement Configuration</title>
    <filename>scorepmeasurementconfig</filename>
    <docanchor file="scorepmeasurementconfig">SCOREP_ENABLE_PROFILING</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ENABLE_TRACING</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ENABLE_UNWINDING</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_VERBOSE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TOTAL_MEMORY</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PAGE_SIZE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_EXPERIMENT_DIRECTORY</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_OVERWRITE_EXPERIMENT_DIRECTORY</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MACHINE_NAME</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_EXECUTABLE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ENABLE_SYSTEM_TREE_SEQUENCE_DEFINITIONS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_FORCE_CFG_FILES</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TIMER</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_NM_SYMBOLS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_DEBUG_UNIFY</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_TASK_EXCHANGE_NUM</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_MAX_CALLPATH_DEPTH</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_BASE_NAME</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_FORMAT</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_ENABLE_CLUSTERING</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_CLUSTER_COUNT</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_CLUSTERING_MODE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_CLUSTERED_REGION</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_PROFILING_ENABLE_CORE_FILES</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TRACING_USE_SION</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TRACING_MAX_PROCS_PER_SION_FILE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TRACING_CONVERT_CALLING_CONTEXT_EVENTS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ONLINEACCESS_ENABLE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ONLINEACCESS_REG_PORT</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ONLINEACCESS_REG_HOST</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ONLINEACCESS_BASE_PORT</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_ONLINEACCESS_APPL_NAME</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_FILTERING_FILE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_SUBSTRATE_PLUGINS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_SUBSTRATE_PLUGINS_SEP</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PAPI</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PAPI_PER_PROCESS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PAPI_SEP</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_RUSAGE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_RUSAGE_PER_PROCESS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_RUSAGE_SEP</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PLUGINS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PLUGINS_SEP</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PERF</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PERF_PER_PROCESS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_METRIC_PERF_SEP</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_SAMPLING_EVENTS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_SAMPLING_SEP</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TOPOLOGY_PLATFORM</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TOPOLOGY_PROCESS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TOPOLOGY_USER</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_TOPOLOGY_MPI</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_SELECTIVE_CONFIG_FILE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_MAX_COMMUNICATORS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_MAX_WINDOWS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_MAX_EPOCHS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_MAX_GROUPS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_ENABLE_GROUPS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_MEMORY_RECORDING</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MPI_ONLINE_ANALYSIS</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_SHMEM_MEMORY_RECORDING</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_CUDA_ENABLE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_CUDA_BUFFER</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_CUDA_BUFFER_CHUNK</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_OPENCL_ENABLE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_OPENCL_BUFFER_QUEUE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_OPENACC_ENABLE</docanchor>
    <docanchor file="scorepmeasurementconfig">SCOREP_MEMORY_RECORDING</docanchor>
  </compound>
  <compound kind="page">
    <name>scorepwrapper</name>
    <title>Score-P Compiler Wrapper Usage</title>
    <filename>scorepwrapper</filename>
  </compound>
  <compound kind="page">
    <name>scoreplibwrap</name>
    <title>Score-P User Library Wrapping</title>
    <filename>scoreplibwrap</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Introduction</title>
    <filename>index</filename>
    <docanchor file="index" title="About this Document">about_doc</docanchor>
    <docanchor file="index" title="Getting Help and Support">getting_help</docanchor>
    <docanchor file="index" title="Basics of Performance Optimization">basic_idea</docanchor>
    <docanchor file="index" title="Score-P Software Architecture Overview">overview</docanchor>
    <docanchor file="index" title="Acknowledgment">acknowledgment</docanchor>
  </compound>
</tagfile>
