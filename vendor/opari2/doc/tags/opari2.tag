<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>opari2_region_info.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/vendor/opari2/src/opari-lib-dummy/</path>
    <filename>opari2__region__info_8h</filename>
    <class kind="struct">OPARI2_Region_info</class>
  </compound>
  <compound kind="file">
    <name>pomp2_lib.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/vendor/opari2/include/opari2/</path>
    <filename>pomp2__lib_8h</filename>
    <member kind="typedef">
      <type>void *</type>
      <name>OPARI2_Region_handle</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a8ae6e761e844cad11e306b839b7065d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Assign_handle</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a4ced2800b4c94cb22193e4a8b9d7a0b2</anchor>
      <arglist>(POMP2_Region_handle *pomp2_handle, const char ctc_string[])</arglist>
    </member>
    <member kind="function">
      <type>POMP2_Task_handle</type>
      <name>POMP2_Get_new_task_handle</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a45c8a37325b33db03c8dc30db0d3f385</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>POMP2_Get_num_regions</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a5677283f76b1775959efa672bd0595af</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Init_regions</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a1ee3934a87de5fb3e14bbef827fc0f4c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>POMP2_Get_opari2_version</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a64540be40e1ccb2a6084608e6b517ca4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>POMP2_Get_num_regions</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a5677283f76b1775959efa672bd0595af</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Init_regions</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a1ee3934a87de5fb3e14bbef827fc0f4c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>POMP2_Get_opari2_version</name>
      <anchorfile>pomp2__lib_8h.html</anchorfile>
      <anchor>a64540be40e1ccb2a6084608e6b517ca4</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pomp2_region_info.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/vendor/opari2/src/opari-lib-dummy/</path>
    <filename>pomp2__region__info_8h</filename>
    <includes id="opari2__region__info_8h" name="opari2_region_info.h" local="yes" imported="no">opari2_region_info.h</includes>
    <class kind="struct">POMP2_Region_info</class>
    <member kind="define">
      <type>#define</type>
      <name>CTC_OMP_TOKENS</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>ac86b4fc4c04b1049b788a9fec71dc8fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>POMP2_DefaultSharing_type</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>a93b8b7fd1fc771580ef1e2c6eefecc59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>POMP2_Region_type</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>a680a7412e9daca09b793c6538fb7b381</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>POMP2_Schedule_type</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>a9bada01c672e9a100dc7903ba06e76a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctcString2RegionInfo</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>ada8fce980385bdc6598a889bc2ba7892</anchor>
      <arglist>(const char ctcString[], POMP2_Region_info *regionInfo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>freePOMP2RegionInfoMembers</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>a328c8dd30c3edae6a9c076f990ea36c6</anchor>
      <arglist>(POMP2_Region_info *regionInfo)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>pomp2defaultSharingType2String</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>ad0856c731e68eef9a148ab79cd0329b1</anchor>
      <arglist>(POMP2_DefaultSharing_type defaultSharingType)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>pomp2RegionType2String</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>a41324a61d69375fcf4d905a2db32a1b5</anchor>
      <arglist>(POMP2_Region_type regionType)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>pomp2ScheduleType2String</name>
      <anchorfile>pomp2__region__info_8h.html</anchorfile>
      <anchor>a5a45288617878806cd3773be2bad8ec4</anchor>
      <arglist>(POMP2_Schedule_type scheduleType)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pomp2_user_lib.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/vendor/opari2/include/opari2/</path>
    <filename>pomp2__user__lib_8h</filename>
    <member kind="typedef">
      <type>void *</type>
      <name>OPARI2_Region_handle</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a8ae6e761e844cad11e306b839b7065d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>POMP2_USER_Get_num_regions</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>ae0dfec7d859997b69bbcda438dca1867</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_USER_Init_regions</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>af54040ee98b4278d5b991a36b813357c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>POMP2_Get_opari2_version</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a64540be40e1ccb2a6084608e6b517ca4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Finalize</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>ae172c40c40ac62b7587e1b11abfff559</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Init</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a973f7b06d14fddd52ed74ee50529c284</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Off</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a07b65ff3417a1f6924b4a1754a5b6260</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_On</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a540cdb76c25649773dcec9fd6a9fac03</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Begin</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a103798c6fcdee1063ff8baf88f13d8ea</anchor>
      <arglist>(POMP2_USER_Region_handle *pomp2_handle, const char ctc_string[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_End</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a94e19dfab1ba91569bc18c057ca5ad37</anchor>
      <arglist>(POMP2_USER_Region_handle *pomp2_handle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_USER_Assign_handle</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a7589f2c2aa05b5bed5c15c9e4f07b701</anchor>
      <arglist>(POMP2_USER_Region_handle *pomp2_handle, const char ctc_string[])</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>POMP2_USER_Get_num_regions</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>ae0dfec7d859997b69bbcda438dca1867</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_USER_Init_regions</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>af54040ee98b4278d5b991a36b813357c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>POMP2_Get_opari2_version</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a64540be40e1ccb2a6084608e6b517ca4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Finalize</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>ae172c40c40ac62b7587e1b11abfff559</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Init</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a973f7b06d14fddd52ed74ee50529c284</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Off</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a07b65ff3417a1f6924b4a1754a5b6260</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_On</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a540cdb76c25649773dcec9fd6a9fac03</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_Begin</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a103798c6fcdee1063ff8baf88f13d8ea</anchor>
      <arglist>(POMP2_USER_Region_handle *pomp2_handle, const char ctc_string[])</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_End</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a94e19dfab1ba91569bc18c057ca5ad37</anchor>
      <arglist>(POMP2_USER_Region_handle *pomp2_handle)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>POMP2_USER_Assign_handle</name>
      <anchorfile>pomp2__user__lib_8h.html</anchorfile>
      <anchor>a7589f2c2aa05b5bed5c15c9e4f07b701</anchor>
      <arglist>(POMP2_USER_Region_handle *pomp2_handle, const char ctc_string[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>pomp2_user_region_info.h</name>
    <path>/CI/build/tmp.q7M7lS4ZbE/src/vendor/opari2/src/opari-lib-dummy/</path>
    <filename>pomp2__user__region__info_8h</filename>
    <includes id="opari2__region__info_8h" name="opari2_region_info.h" local="yes" imported="no">opari2_region_info.h</includes>
    <class kind="struct">POMP2_USER_Region_info</class>
    <member kind="define">
      <type>#define</type>
      <name>CTC_USER_REGION_TOKENS</name>
      <anchorfile>pomp2__user__region__info_8h.html</anchorfile>
      <anchor>a93fefda49d7492bf924809e8b6b6ee77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>POMP2_USER_Region_type</name>
      <anchorfile>pomp2__user__region__info_8h.html</anchorfile>
      <anchor>ae76f4de310f343b64c6541b68ef60600</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ctcString2UserRegionInfo</name>
      <anchorfile>pomp2__user__region__info_8h.html</anchorfile>
      <anchor>adf68daa6bcbb49e313189a50c692217a</anchor>
      <arglist>(const char ctcString[], POMP2_USER_Region_info *regionInfo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>freePOMP2UserRegionInfoMembers</name>
      <anchorfile>pomp2__user__region__info_8h.html</anchorfile>
      <anchor>af2baca6fe4127338e932a68d84af374f</anchor>
      <arglist>(POMP2_USER_Region_info *regionInfo)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>pomp2UserRegionType2String</name>
      <anchorfile>pomp2__user__region__info_8h.html</anchorfile>
      <anchor>aea1b2a34dad1e46141aa650948fbacfb</anchor>
      <arglist>(POMP2_USER_Region_type regionType)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>OPARI2_Region_info</name>
    <filename>structOPARI2__Region__info.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>mEndFileName</name>
      <anchorfile>structOPARI2__Region__info.html</anchorfile>
      <anchor>aa33fdbf1549f6429201ee0293e7c3fc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine1</name>
      <anchorfile>structOPARI2__Region__info.html</anchorfile>
      <anchor>a79fa5ad783540110f20895c447d1744b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine2</name>
      <anchorfile>structOPARI2__Region__info.html</anchorfile>
      <anchor>a69ae9b2133cfc45a05348c9e942cff14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mStartFileName</name>
      <anchorfile>structOPARI2__Region__info.html</anchorfile>
      <anchor>afe9ce03c86b5a601fc5d5a02f364d10e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine1</name>
      <anchorfile>structOPARI2__Region__info.html</anchorfile>
      <anchor>afe9d460b353581336ef01828f36c532a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine2</name>
      <anchorfile>structOPARI2__Region__info.html</anchorfile>
      <anchor>a00a8fe35010120cc7bf9a69aab78428d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>POMP2_Region_info</name>
    <filename>structPOMP2__Region__info.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>mStartFileName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a6034a8b8c7b55bc7979977b9334958db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine1</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a9f0d2a2d58e6ee5e23b2b1e0a1d4ebc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine2</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a5685e6673c14de2660bf224eaa554b76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mEndFileName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a8c0105ca03822a142662e80953d75358</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine1</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a94d58f08bbf8e8529fedb7cbccffd017</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine2</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>ade27fd75d1537732a2459c78f818eb8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>POMP2_Region_type</type>
      <name>mRegionType</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a34a3ca3ada9bbf45ae4f1e8248b13e70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasCopyIn</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a2f7f3d1dc98587dbff386c6d8e38b96b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasCopyPrivate</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a4bf7f82ec65b0115b0a929e307c1bf58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasIf</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>afaf850aae51e3e80f1566ee8fbf836f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasFirstPrivate</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a4087657089faf52b1d6edc383388ff85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasLastPrivate</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a8e6ec810e13638ac587810f23678487c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasNoWait</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a5f2a12e99defcacafcba38d7c161e89d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasNumThreads</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>af9ecc5af683aba508fb892b2738bbdc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasOrdered</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a24a152ec56e0eafe41326d1d0329bc9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasReduction</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a629015eae4cec0d4bc7e0da0f0dfaeff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasShared</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a127860ebef450e083a0100ddbb3b42a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasCollapse</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a80c536c6186f3c61f0358b073a302571</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasUntied</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a8790f498cf86eb6808a9df5d01449677</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>POMP2_Schedule_type</type>
      <name>mScheduleType</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>aeaa2f47c4731b4e10dd3bfb35a2024a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>POMP2_DefaultSharing_type</type>
      <name>mDefaultSharingType</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>abd19d390e07d1ed760ce07bc8e1ec915</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mUserGroupName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>ae8cebc481d4414f0857d96080ca16a8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mNumSections</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a63d659e3d853a16e7dc2364a345af231</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mCriticalName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a4e4565e6d2c2881d007ab343769f6766</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mStartFileName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a6034a8b8c7b55bc7979977b9334958db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine1</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a9f0d2a2d58e6ee5e23b2b1e0a1d4ebc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine2</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a5685e6673c14de2660bf224eaa554b76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mEndFileName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a8c0105ca03822a142662e80953d75358</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine1</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a94d58f08bbf8e8529fedb7cbccffd017</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine2</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>ade27fd75d1537732a2459c78f818eb8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>POMP2_Region_type</type>
      <name>mRegionType</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a34a3ca3ada9bbf45ae4f1e8248b13e70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasCopyIn</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a2f7f3d1dc98587dbff386c6d8e38b96b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasCopyPrivate</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a4bf7f82ec65b0115b0a929e307c1bf58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasIf</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>afaf850aae51e3e80f1566ee8fbf836f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasFirstPrivate</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a4087657089faf52b1d6edc383388ff85</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasLastPrivate</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a8e6ec810e13638ac587810f23678487c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasNoWait</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a5f2a12e99defcacafcba38d7c161e89d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasNumThreads</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>af9ecc5af683aba508fb892b2738bbdc5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasOrdered</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a24a152ec56e0eafe41326d1d0329bc9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasReduction</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a629015eae4cec0d4bc7e0da0f0dfaeff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasShared</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a127860ebef450e083a0100ddbb3b42a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasCollapse</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a80c536c6186f3c61f0358b073a302571</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>mHasUntied</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a8790f498cf86eb6808a9df5d01449677</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>POMP2_Schedule_type</type>
      <name>mScheduleType</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>aeaa2f47c4731b4e10dd3bfb35a2024a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>POMP2_DefaultSharing_type</type>
      <name>mDefaultSharingType</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>abd19d390e07d1ed760ce07bc8e1ec915</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mUserGroupName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>ae8cebc481d4414f0857d96080ca16a8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mNumSections</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a63d659e3d853a16e7dc2364a345af231</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mCriticalName</name>
      <anchorfile>structPOMP2__Region__info.html</anchorfile>
      <anchor>a4e4565e6d2c2881d007ab343769f6766</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>POMP2_USER_Region_info</name>
    <filename>structPOMP2__USER__Region__info.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>mStartFileName</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>a2f92dfc397a0dbc804e55c4ab7ac2eef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine1</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>adad6ea05f301f28eabb3896fe0fe712f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine2</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>afd6302572b35de605e7442e0824b7ae0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mEndFileName</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>aecc81da4f774c976d884b6ae537d5cf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine1</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>a199ea4217019eda9cf853871a26e4340</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine2</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>aa6690583d3f6a7766d016dd527ffd4e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mUserRegionName</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>a42d60ea34302fba9dc19dfa189c79aae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mStartFileName</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>a2f92dfc397a0dbc804e55c4ab7ac2eef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine1</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>adad6ea05f301f28eabb3896fe0fe712f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mStartLine2</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>afd6302572b35de605e7442e0824b7ae0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mEndFileName</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>aecc81da4f774c976d884b6ae537d5cf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine1</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>a199ea4217019eda9cf853871a26e4340</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>mEndLine2</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>aa6690583d3f6a7766d016dd527ffd4e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>mUserRegionName</name>
      <anchorfile>structPOMP2__USER__Region__info.html</anchorfile>
      <anchor>a42d60ea34302fba9dc19dfa189c79aae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>INSTALL</name>
    <title>Installation</title>
    <filename>INSTALL</filename>
  </compound>
  <compound kind="page">
    <name>USAGE</name>
    <title>Basic Usage</title>
    <filename>USAGE</filename>
  </compound>
  <compound kind="page">
    <name>CTC_STRING</name>
    <title>CTC-String Decoding</title>
    <filename>CTC_STRING</filename>
    <docanchor file="CTC_STRING">OpenMP</docanchor>
  </compound>
  <compound kind="page">
    <name>LINKING</name>
    <title>Linking to a Measurement System</title>
    <filename>LINKING</filename>
  </compound>
  <compound kind="page">
    <name>POMP_USER</name>
    <title>POMP User Instrumentation</title>
    <filename>POMP_USER</filename>
  </compound>
  <compound kind="page">
    <name>EXAMPLE</name>
    <title>Example Code</title>
    <filename>EXAMPLE</filename>
  </compound>
  <compound kind="page">
    <name>NEWS</name>
    <title>Latest Release News</title>
    <filename>NEWS</filename>
    <docanchor file="NEWS" title="Modularization">MODULARIZTION</docanchor>
    <docanchor file="NEWS" title="LINK STEP">LINK_STEP</docanchor>
    <docanchor file="NEWS" title="POMP2">POMP2</docanchor>
    <docanchor file="NEWS" title="POMP2_Parallel_fork">POMP2_Parallel_fork</docanchor>
    <docanchor file="NEWS" title="pomp_tpd">pomp_tpd</docanchor>
    <docanchor file="NEWS" title="Tasking construct">TASKING</docanchor>
    <docanchor file="NEWS" title="Preprocessing of source files">Preprocessing_of_source_files</docanchor>
  </compound>
  <compound kind="page">
    <name>installationfile</name>
    <title>OPARI2 INSTALL</title>
    <filename>installationfile</filename>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>OPARI2 - Introduction and Contents</title>
    <filename>index</filename>
    <docanchor file="index" title="User documentation contents">content</docanchor>
    <docanchor file="index">SUMMARY</docanchor>
  </compound>
</tagfile>
