benchmarks = [
    # sv-comp/array-cav19
    {
        "name": "array_doub_access_init_const.c",
        "relative_path": "./sv-comp/array-cav19/array_doub_access_init_const.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "emp",
                "absint_domain": "polka",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_nondet_vars.c",
        "relative_path": "./sv-comp/array-cav19/array_init_nondet_vars.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "mix_data_indexes": True,
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_pair_sum_const.c",
        "relative_path": "./sv-comp/array-cav19/array_init_pair_sum_const.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_pair_symmetr.c",
        "relative_path": "./sv-comp/array-cav19/array_init_pair_symmetr.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "emp",
                "data_domain": "oct",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_pair_symmetr2.c",
        "relative_path": "./sv-comp/array-cav19/array_init_pair_symmetr2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "emp",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_var_plus_ind.c",
        "relative_path": "./sv-comp/array-cav19/array_init_var_plus_ind.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_var_plus_ind2.c",
        "relative_path": "./sv-comp/array-cav19/array_init_var_plus_ind2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_init_var_plus_ind3.c",
        "relative_path": "./sv-comp/array-cav19/array_init_var_plus_ind3.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_min_and_copy_shift_sum_add.c",
        "relative_path": "./sv-comp/array-cav19/array_min_and_copy_shift_sum_add.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "mix_data_indexes": True,
                "index_domain": "int+oct",
                "data_domain": "int+oct",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_tiling_poly6.c",
        "relative_path": "./sv-comp/array-cav19/array_tiling_poly6.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": True,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "emp",
                "absint_domain": "polka",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_tiling_tcpy.c",
        "relative_path": "./sv-comp/array-cav19/array_tiling_tcpy.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "polka",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_tripl_access_init_const.c",
        "relative_path": "./sv-comp/array-cav19/array_tripl_access_init_const.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "polka",
                "quantifiers": 1
            }
        }
    },
    # sv-comp/array-examples
    {
        "name": "data_structures_set_multi_proc_ground-1.c",
        "relative_path": "./sv-comp/array-examples/data_structures_set_multi_proc_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT # TODO: debug why we get the same counterexample
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "data_structures_set_multi_proc_ground-2.c",
        "relative_path": "./sv-comp/array-examples/data_structures_set_multi_proc_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int+oct",
                "data_domain": "int+oct",
                "absint_domain": "polka",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "data_structures_set_multi_proc_trivial_ground.c",
        "relative_path": "./sv-comp/array-examples/data_structures_set_multi_proc_trivial_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int+oct",
                "data_domain": "int+oct",
                "absint_domain": "polka",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "sanfoundry_02_ground.c",
        "relative_path": "./sv-comp/array-examples/sanfoundry_02_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "sanfoundry_10_ground.c",
        "relative_path": "./sv-comp/array-examples/sanfoundry_10_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "sanfoundry_24-1.c",
        "relative_path": "./sv-comp/array-examples/sanfoundry_24-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": True,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "sanfoundry_24-2.c",
        "relative_path": "./sv-comp/array-examples/sanfoundry_24-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": True,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "sanfoundry_27_ground.c",
        "relative_path": "./sv-comp/array-examples/sanfoundry_27_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "sorting_bubblesort_2_ground.c",
        "relative_path": "./sv-comp/array-examples/sorting_bubblesort_2_ground.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "sorting_bubblesort_ground-1.c",
        "relative_path": "./sv-comp/array-examples/sorting_bubblesort_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 2
            }
        }
    },
    {
        "name": "sorting_bubblesort_ground-2.c",
        "relative_path": "./sv-comp/array-examples/sorting_bubblesort_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "sorting_selectionsort_2_ground.c",
        "relative_path": "./sv-comp/array-examples/sorting_selectionsort_2_ground.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "sorting_selectionsort_ground-1.c",
        "relative_path": "./sv-comp/array-examples/sorting_selectionsort_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "sorting_selectionsort_ground-2.c",
        "relative_path": "./sv-comp/array-examples/sorting_selectionsort_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "standard_allDiff2_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_allDiff2_ground.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "standard_compare_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_compare_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_compareModified_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_compareModified_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy1_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy1_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy1_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy1_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2  # TODO: automatic quantifier number incrementation
            }
        }
    },
    {
        "name": "standard_copy2_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy2_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "standard_copy2_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy2_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy3_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy3_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy3_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy3_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy4_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy4_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy4_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy4_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy5_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy5_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy5_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy5_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy6_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy6_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy6_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy6_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy7_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy7_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy7_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy7_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy8_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy8_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy8_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy8_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy9_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_copy9_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copy9_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_copy9_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_copyInit_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_copyInit_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_find_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_find_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_find_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_find_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init1_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init1_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init1_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init1_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init2_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init2_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init2_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init2_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init3_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init3_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init3_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init3_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init4_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init4_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init4_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init4_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init5_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init5_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init5_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init5_ground-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init6_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init6_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init6_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init6_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init7_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init7_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init7_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init7_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init8_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init8_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init8_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init8_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init9_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_init9_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_init9_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_init9_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_maxInArray_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_maxInArray_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_minInArray_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_minInArray_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_minInArray_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_minInArray_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_palindrome_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_palindrome_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "standard_partial_init_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_partial_init_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_partition_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_partition_ground-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_partition_ground-2.c",
        "relative_path": "./sv-comp/array-examples/standard_partition_ground-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_partition_original_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_partition_original_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_password_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_password_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_reverse_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_reverse_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_running-1.c",
        "relative_path": "./sv-comp/array-examples/standard_running-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_running-2.c",
        "relative_path": "./sv-comp/array-examples/standard_running-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_sentinel-1.c",
        "relative_path": "./sv-comp/array-examples/standard_sentinel-1.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_sentinel-2.c",
        "relative_path": "./sv-comp/array-examples/standard_sentinel-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_seq_init_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_seq_init_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 2
            }
        }
    },
    {
        "name": "standard_strcmp_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_strcmp_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_strcpy_ground-1.c",
        "relative_path": "./sv-comp/array-examples/standard_strcpy_ground-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_strcpy_original-2.c",
        "relative_path": "./sv-comp/array-examples/standard_strcpy_original-2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "int+eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "standard_two_index_01.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_01.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_02.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_02.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_03.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_03.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_04.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_04.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_05.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_05.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_06.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_06.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_07.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_07.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_08.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_08.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_two_index_09.c",
        "relative_path": "./sv-comp/array-examples/standard_two_index_09.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "standard_vector_difference_ground.c",
        "relative_path": "./sv-comp/array-examples/standard_vector_difference_ground.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    # sv-comp/array-industry-pattern
    {
        "name": "array_assert_loop_dep.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_assert_loop_dep.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "abstract-big-indexes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_monotonic.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_monotonic.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "kmod0",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_mul_init.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_mul_init.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": True,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_ptr_single_elem_init-2.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_ptr_single_elem_init-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": True,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "parametrize-value-w-parametric-value": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_range_init.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_range_init.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "parametrize-value-w-parametric-value": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_shadowinit.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_shadowinit.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array_single_elem_init.c",
        "relative_path": "./sv-comp/array-industry-pattern/array_single_elem_init.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "parametrize-value-w-parametric-value": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "check_removal_from_set_after_insertion.c",
        "relative_path": "./sv-comp/array-industry-pattern/check_removal_from_set_after_insertion.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    # sv-comp/array-lopstr16
    {
        "name": "partial_lesser_bound-1.c",
        "relative_path": "./sv-comp/array-lopstr16/partial_lesser_bound-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    # sv-comp/array-programs
    {
        "name": "copysome1-1.c",
        "relative_path": "./sv-comp/array-programs/copysome1-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "abstract-big-indexes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "copysome1-2.c",
        "relative_path": "./sv-comp/array-programs/copysome1-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "abstract-big-indexes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "copysome2-1.c",
        "relative_path": "./sv-comp/array-programs/copysome2-1.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "abstract-big-indexes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "copysome2-2.c",
        "relative_path": "./sv-comp/array-programs/copysome2-2.c",
        "expected_verdict": "unsafe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
            "abstract-big-indexes": True
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "int",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    # sv-comp/array-tiling
    {
        "name": "mbpr2.c",
        "relative_path": "./sv-comp/array-tiling/mbpr2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "mbpr3.c",
        "relative_path": "./sv-comp/array-tiling/mbpr3.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "mbpr4.c",
        "relative_path": "./sv-comp/array-tiling/mbpr4.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "mbpr5.c",
        "relative_path": "./sv-comp/array-tiling/mbpr5.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "nr2.c",
        "relative_path": "./sv-comp/array-tiling/nr2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "mix_data_indexes": True,
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "nr3.c",
        "relative_path": "./sv-comp/array-tiling/nr3.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "mix_data_indexes": True,
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "nr4.c",
        "relative_path": "./sv-comp/array-tiling/nr4.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "mix_data_indexes": True,
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "nr5.c",
        "relative_path": "./sv-comp/array-tiling/nr5.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "mix_data_indexes": True,
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "pr2.c",
        "relative_path": "./sv-comp/array-tiling/pr2.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "pr3.c",
        "relative_path": "./sv-comp/array-tiling/pr3.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "pr4.c",
        "relative_path": "./sv-comp/array-tiling/pr4.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "pr5.c",
        "relative_path": "./sv-comp/array-tiling/pr5.c",
        "expected_verdict": "safe",
        "source": "sv-comp",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "modifications": {
            "parametrize-array-sizes": True,
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+kmod0",
                "data_domain": "int",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    # tapis-bench/iterative
    {
        "name": "array-argmin-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-argmin-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-argmax-both.c",
        "relative_path": "./tapis-bench/iterative/array-argmax-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-is-subarray-at-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-is-subarray-at-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "polka",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-max-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-max-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-partial-init-0-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-partial-init-0-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-strong-spec-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-find-strong-spec-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-argmin-both.c",
        "relative_path": "./tapis-bench/iterative/array-argmin-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-merge.c",
        "relative_path": "./tapis-bench/iterative/array-merge.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "polka",
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-find-strong-spec-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-find-strong-spec-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-partial-init-0-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-partial-init-0-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-max-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-max-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-both.c",
        "relative_path": "./tapis-bench/iterative/array-find-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-copy-both.c",
        "relative_path": "./tapis-bench/iterative/array-copy-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmin-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-argmin-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-compare-both.c",
        "relative_path": "./tapis-bench/iterative/array-compare-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-init-0-both.c",
        "relative_path": "./tapis-bench/iterative/array-init-0-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insert-last.c",
        "relative_path": "./tapis-bench/iterative/array-insert-last.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-partition-ver-lomuto.c",
        "relative_path": "./tapis-bench/iterative/array-partition-ver-lomuto.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "attr_from_spec": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-sorted-find.c",
        "relative_path": "./tapis-bench/iterative/array-sorted-find.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-reverse-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-reverse-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-selection-sort-ver-1.c",
        "relative_path": "./tapis-bench/iterative/array-selection-sort-ver-1.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-max-both.c",
        "relative_path": "./tapis-bench/iterative/array-max-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-copy-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-copy-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insert-first.c",
        "relative_path": "./tapis-bench/iterative/array-insert-first.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-insertion-sort-ver-1.c",
        "relative_path": "./tapis-bench/iterative/array-insertion-sort-ver-1.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-find-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-find-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-min-both.c",
        "relative_path": "./tapis-bench/iterative/array-min-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-bubble-sort-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-bubble-sort-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-sorted-find-strong-spec.c",
        "relative_path": "./tapis-bench/iterative/array-sorted-find-strong-spec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-bubble-sort-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-bubble-sort-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-find-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-find-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-copy-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-copy-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-strong-spec-both.c",
        "relative_path": "./tapis-bench/iterative/array-find-strong-spec-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-reverse-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-reverse-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmax-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-argmax-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-init-0-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-init-0-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-reverse-both.c",
        "relative_path": "./tapis-bench/iterative/array-reverse-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-selection-sort-ver-2.c",
        "relative_path": "./tapis-bench/iterative/array-selection-sort-ver-2.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "prophic3", "updria"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-compare-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-compare-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-min-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-min-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insertion-sort-ver-2.c",
        "relative_path": "./tapis-bench/iterative/array-insertion-sort-ver-2.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-subarray.c",
        "relative_path": "./tapis-bench/iterative/array-subarray.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # TIMEOUT
                "index_domain": "ub+int",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-min-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-min-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-compare-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-compare-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "vajra", "diffy", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-init-0-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-init-0-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmax-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-argmax-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-init-i-fwd.c",
        "relative_path": "./tapis-bench/iterative/array-init-i-fwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "vajra", "diffy", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "emp",
                "data_domain": "emp",
                "absint_domain": "oct",
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-init-i-bwd.c",
        "relative_path": "./tapis-bench/iterative/array-init-i-bwd.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "mix_data_indexes": True,
                "index_domain": "ub",
                "data_domain": "emp",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-init-i-both.c",
        "relative_path": "./tapis-bench/iterative/array-init-i-both.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": True,
            "aggregation": False,
            "procedures": False,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "freqhorn", "ultimate-automizer", "prophic3", "rapid"],
        "parameters": {
            "tapis": {  # DOABLE
                "mix_data_indexes": True,
                "index_domain": "ub",
                "data_domain": "emp",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    # tapis-bench/rec
    {
        "name": "array-copy-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-copy-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-copy-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-copy-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-max-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-max-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-strong-spec-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-find-strong-spec-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-init-0-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-init-0-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insert-last-rec.c",
        "relative_path": "./tapis-bench/rec/array-insert-last-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-partial-init-0-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-partial-init-0-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "abstract_summary_input_arrays": True,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-bubble-sort-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-bubble-sort-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-compare-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-compare-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-quick-sort.c",
        "relative_path": "./tapis-bench/rec/array-quick-sort.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "attr_from_spec": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-argmin-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-argmin-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-min-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-min-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-find-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-strong-spec-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-find-strong-spec-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insertion-sort-ver-rec-without-insert.c",
        "relative_path": "./tapis-bench/rec/array-insertion-sort-ver-rec-without-insert.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-max-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-max-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmax-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-argmax-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-argmin-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-argmin-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-compare-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-compare-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insertion-sort-ver-rec.c",
        "relative_path": "./tapis-bench/rec/array-insertion-sort-ver-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-find-strong-spec-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-find-strong-spec-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-init-0-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-init-0-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-find-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-min-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-min-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmin-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-argmin-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-min-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-min-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmax-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-argmax-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-max-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-max-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-find-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "int+ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-copy-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-copy-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-init-0-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-init-0-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-bubble-sort-bwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-bubble-sort-bwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-quick-sort-without-partition.c",
        "relative_path": "./tapis-bench/rec/array-quick-sort-without-partition.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "attr_from_spec": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-compare-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-compare-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-argmax-both-rec.c",
        "relative_path": "./tapis-bench/rec/array-argmax-both-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-partial-init-0-fwd-rec.c",
        "relative_path": "./tapis-bench/rec/array-partial-init-0-fwd-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": False
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "abstract_summary_input_arrays": True,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-insert-first-rec.c",
        "relative_path": "./tapis-bench/rec/array-insert-first-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    # tapis-bench/mut-rec
    {
        "name": "array-argmax-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-argmax-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-argmin-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-argmin-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-compare-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-compare-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-find-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-find-strong-spec-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-find-strong-spec-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub+int",
                "data_domain": "eq",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 2
            }
        }
    },
    {
        "name": "array-init-0-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-init-0-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "int",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-max-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-max-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
    {
        "name": "array-min-both-mutual-rec.c",
        "relative_path": "./tapis-bench/mut-rec/array-min-both-mutual-rec.c",
        "expected_verdict": "safe",
        "source": "tapis-bench",
        "features": {
            "arrays": True,
            "infinite-arrays": False,
            "NIA": False,
            "index-data-mixing": False,
            "aggregation": False,
            "procedures": True,
            "recursive-procedures": True
        },
        "supported_by": ["tapis", "spacer", "ultimate-automizer", "monocera"],
        "parameters": {
            "tapis": {  # DOABLE
                "index_domain": "ub",
                "data_domain": "ub",
                "absint_domain": "oct",
                "attr_from_program": False,
                "quantifiers": 1
            }
        }
    },
]


def get_benchmark_info(name):
    for b in benchmarks:
        if b["name"] == name:
            return b
    return None
